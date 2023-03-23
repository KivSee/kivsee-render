#include <effect/snake.h>
#include <effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        float getBrightnessFactor(float rel_pos, float curr_head, float curr_tail_length) {
            float curr_tail = curr_head - curr_tail_length;
            bool isOutsideRange = (rel_pos > curr_head || rel_pos < curr_tail);
            if (isOutsideRange) {
                return 0;
            } else {
                return (rel_pos - curr_tail) / curr_tail_length;
            }
        }

        void Snake::Render(float rel_time, int cycle_index)
        {
            const float curr_config_head = head->GetValue(rel_time);
            const float curr_tail_length = tail_length->GetValue(rel_time);

            const float curr_head = cyclic ? (curr_config_head - (int)curr_config_head) : curr_config_head;
            const float curr_tail = curr_config_head - curr_tail_length;

            if (curr_tail_length == 0) {
                for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
                {
                    HSV *pixel = it->pixel;
                    pixel->val *= 0;
                }
            } else {
                for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
                {
                    HSV *pixel = it->pixel;
                    float rel_pos = it->relativePositionInSegment;
                    float cyclic_head = curr_head;
                    if(cyclic && rel_pos > curr_head) {
                        cyclic_head += 1.0;
                    }
                    float brightness_factor = getBrightnessFactor(rel_pos, cyclic_head, curr_tail_length);
                    pixel->val *= brightness_factor;
                }
            }
        }

        bool Snake::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            SnakeEffectConfig config = SnakeEffectConfig_init_zero;

            float_functions::IFloatFunction *head;
            float_functions::IFloatFunction *tail_length;

            config.head.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.head.arg = &head;
            config.tail_length.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.tail_length.arg = &tail_length;

            if (!pb_decode(stream, SnakeEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new Snake(head, tail_length, config.cyclic);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render