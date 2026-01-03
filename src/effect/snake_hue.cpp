#include <effect/snake_hue.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        void SnakeHue::Render(float rel_time, int cycle_index)
        {
            const float curr_config_head = head->GetValue(rel_time);
            const float curr_tail_length = tail_length->GetValue(rel_time);

            // Handle cyclic mode: wrap head position to [0, 1)
            const float curr_head = cyclic ? (curr_config_head - (int)curr_config_head) : curr_config_head;
            
            // Calculate tail position
            const float curr_tail = curr_head - curr_tail_length;

            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                float rel_pos = it->relativePositionInSegment;
                
                bool is_in_snake = false;
                float snake_index = 0.0f;
                
                if (cyclic && curr_tail < 0.0f)
                {
                    // Snake wraps around: tail portion is at end of segment, head portion is at start
                    float wrapped_tail = curr_tail + 1.0f;
                    
                    if (rel_pos >= wrapped_tail)
                    {
                        // Pixel is in the tail portion (wrapped around)
                        is_in_snake = true;
                        snake_index = (rel_pos - wrapped_tail) / curr_tail_length;
                    }
                    else if (rel_pos <= curr_head)
                    {
                        // Pixel is in the head portion
                        is_in_snake = true;
                        // Calculate index: distance from tail end (which is at wrapped_tail)
                        // For head portion, we need to account for the wrap
                        float distance_from_tail = (1.0f - wrapped_tail) + rel_pos;
                        snake_index = distance_from_tail / curr_tail_length;
                    }
                }
                else
                {
                    // Non-cyclic or snake doesn't wrap around
                    if (rel_pos >= curr_tail && rel_pos <= curr_head)
                    {
                        is_in_snake = true;
                        if (curr_tail_length > 0)
                        {
                            snake_index = (rel_pos - curr_tail) / curr_tail_length;
                        }
                        else
                        {
                            // Zero tail length means only head pixel
                            snake_index = 1.0f;
                        }
                    }
                }
                
                if (!is_in_snake)
                {
                    // Pixel is outside the snake, don't modify it
                    continue;
                }
                
                // Clamp snake_index to [0, 1] to handle floating point precision issues
                if (snake_index < 0.0f) snake_index = 0.0f;
                if (snake_index > 1.0f) snake_index = 1.0f;
                
                // Get offset factor based on position in snake
                float hue_offset = offset_factor->GetValue(snake_index);
                
                // Apply hue offset
                pixel->hue += hue_offset;
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

