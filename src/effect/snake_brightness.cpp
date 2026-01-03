#include <effect/snake_brightness.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        void SnakeBrightness::Render(float rel_time, int cycle_index)
        {
            const float curr_config_head = head->GetValue(rel_time);
            const float curr_tail_length = tail_length->GetValue(rel_time);

            // Handle cyclic mode: wrap head position to [0, 1)
            const float curr_head = cyclic ? (curr_config_head - (int)curr_config_head) : curr_config_head;
            
            // Calculate tail position
            const float curr_tail = curr_head - curr_tail_length;

            // Select which multiplier function to use
            const float_functions::IFloatFunction *mult_factor_func = mult_factor_increase != nullptr ? mult_factor_increase : mult_factor_decrease;

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
                
                // Get multiplier factor based on position in snake
                float mult_factor = mult_factor_func->GetValue(snake_index);
                
                // Apply brightness adjustment
                if (mult_factor_increase != nullptr)
                {
                    // Increase: linearly interpolate from current value to 1.0
                    // factor 1 -> push to 1.0, factor 0 -> keep as is
                    pixel->val = pixel->val + (1.0f - pixel->val) * mult_factor;
                }
                else
                {
                    // Decrease: multiply by the factor
                    pixel->val *= mult_factor;
                }
            }
        }

        bool SnakeBrightness::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_SnakeBrightnessEffectConfig config = kivsee_proto_render_v1_SnakeBrightnessEffectConfig_init_zero;

            float_functions::IFloatFunction *head;
            float_functions::IFloatFunction *tail_length;
            float_functions::IFloatFunction *mult_factor_increase = nullptr;
            float_functions::IFloatFunction *mult_factor_decrease = nullptr;

            config.head.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.head.arg = &head;
            config.tail_length.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.tail_length.arg = &tail_length;
            config.mult_factor_increase.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.mult_factor_increase.arg = &mult_factor_increase;
            config.mult_factor_decrease.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.mult_factor_decrease.arg = &mult_factor_decrease;

            if (!pb_decode(stream, kivsee_proto_render_v1_SnakeBrightnessEffectConfig_fields, &config))
            {
                return false;
            }

            if (mult_factor_increase == nullptr && mult_factor_decrease == nullptr)
            {
                return false;
            }

            *((Effect **)*arg) = new SnakeBrightness(head, tail_length, config.cyclic, config.repeat_num, mult_factor_increase, mult_factor_decrease);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render

