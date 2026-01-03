#include <effect/timed_saturation.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        void TimedSaturation::Render(float rel_time, int cycle_index)
        {
            const float_functions::IFloatFunction *mult_factor_func = mult_factor_increase != nullptr ? mult_factor_increase : mult_factor_decrease;
            const float curr_mult_factor = mult_factor_func->GetValue(rel_time);

            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                if (mult_factor_increase != nullptr)
                {
                    // Increase: linearly interpolate from current value to 1.0
                    // factor 1 -> push to 1.0, factor 0 -> keep as is
                    pixel->sat = pixel->sat + (1.0f - pixel->sat) * curr_mult_factor;
                }
                else
                {
                    // Decrease: multiply by the factor
                    pixel->sat *= curr_mult_factor;
                }
            }
        }

        bool TimedSaturation::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_TimedSaturationEffectConfig config = kivsee_proto_render_v1_TimedSaturationEffectConfig_init_zero;

            float_functions::IFloatFunction *mult_factor_increase = nullptr;
            float_functions::IFloatFunction *mult_factor_decrease = nullptr;

            config.mult_factor_increase.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.mult_factor_increase.arg = &mult_factor_increase;
            config.mult_factor_decrease.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.mult_factor_decrease.arg = &mult_factor_decrease;

            if (!pb_decode(stream, kivsee_proto_render_v1_TimedSaturationEffectConfig_fields, &config))
            {
                return false;
            }

            if (mult_factor_increase == nullptr && mult_factor_decrease == nullptr)
            {
                return false;
            }

            *((Effect **)*arg) = new TimedSaturation(mult_factor_increase, mult_factor_decrease);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render

