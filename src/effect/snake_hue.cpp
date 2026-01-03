#include <effect/snake_hue.h>
#include <effect/snake.h>
#include <kivsee/proto/render/v1/effects.pb.h>
#include <limits>

namespace kivsee_render
{
    namespace effect
    {
        void SnakeHue::ClearPixels()
        {
            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                pixel->val = 0;
            }
        }

        std::pair<float, float> SnakeHue::ExtractHeadPixels(float curr_head, float curr_tail_length)
        {
            float next_pixel_head = std::numeric_limits<float>::infinity();
            float current_pixel_head = -std::numeric_limits<float>::infinity();
            // find the next pixel after the head for a smooth transition
            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                // we know the position of the current head,
                // and looking for the index of the pixel with the closest relPos after it
                float rel_pos = it->relativePositionInSegment;
                if (rel_pos > curr_head && rel_pos < next_pixel_head)
                {
                    next_pixel_head = rel_pos;
                }
                else if (rel_pos <= curr_head && rel_pos > current_pixel_head)
                {
                    current_pixel_head = rel_pos;
                }
            }
            return std::make_pair(current_pixel_head, next_pixel_head);
        }

        void SnakeHue::Render(float rel_time, int cycle_index)
        {
            const float curr_config_head = head->GetValue(rel_time);
            const float curr_tail_length = tail_length->GetValue(rel_time);

            const float curr_head = cyclic ? (curr_config_head - (int)curr_config_head) : curr_config_head;

            if (curr_tail_length == 0)
            {
                return this->ClearPixels();
            }

            std::pair<float, float> head_pixels = ExtractHeadPixels(curr_head, curr_tail_length);
            float current_pixel_head = head_pixels.first;
            float next_head_pixel = head_pixels.second;

            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                float rel_pos = it->relativePositionInSegment;
                float pos_offset_factor = offset_factor->GetValue(rel_pos);
                
                if (rel_pos == next_head_pixel) {
                    pixel->val *= 1.0 - (next_head_pixel - curr_head) / (next_head_pixel - current_pixel_head);
                    pixel->hue += pos_offset_factor;
                    continue;
                }

                float cyclic_head = curr_head;
                if (cyclic && rel_pos > curr_head)
                {
                    cyclic_head += 1.0;
                }
                float brightness_factor = getBrightnessFactor(rel_pos, cyclic_head, curr_tail_length);
                
                // Apply hue offset based on position
                pixel->hue += pos_offset_factor;
                pixel->val *= brightness_factor;
            }
        }

        bool SnakeHue::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_SnakeHueEffectConfig config = kivsee_proto_render_v1_SnakeHueEffectConfig_init_zero;

            float_functions::IFloatFunction *head;
            float_functions::IFloatFunction *tail_length;
            float_functions::IFloatFunction *offset_factor;

            config.head.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.head.arg = &head;
            config.tail_length.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.tail_length.arg = &tail_length;
            config.offset_factor.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.offset_factor.arg = &offset_factor;

            if (!pb_decode(stream, kivsee_proto_render_v1_SnakeHueEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new SnakeHue(head, tail_length, config.cyclic, config.repeat_num, offset_factor);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render

