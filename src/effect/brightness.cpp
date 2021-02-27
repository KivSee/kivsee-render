#include <effect/brightness.h>
#include <Arduino.h>
#include <effects.pb.h>

namespace kivsee_render
{
    namespace color
    {
        void Brightness::Render(float rel_time, int cycle_index)
        {
            const float curr_mult_factor = mult_factor->GetValue(rel_time);

            for (int i = 0; i < pixels->size(); i++)
            {
                HSV *pixel = (*pixels)[i];
                pixel->val *= curr_mult_factor;
            }
        }

        bool Brightness::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            BrightnessEffectConfig config = BrightnessEffectConfig_init_zero;

            float_functions::IFloatFunction *mult_factor;

            config.mult_factor.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.mult_factor.arg = &mult_factor;

            if (!pb_decode(stream, BrightnessEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new Brightness(mult_factor);
            return true;
        }

    } // namespace color
} // namespace kivsee_render