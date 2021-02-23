#include <effect/hue.h>
#include <Arduino.h>
#include <effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        void Hue::Render(float rel_time, int cycle_index)
        {
            const float curr_offset_factor = offset_factor->GetValue(rel_time);

            for (int i = 0; i < pixels->size(); i++)
            {
                HSV *pixel = (*pixels)[i];
                pixel->hue += curr_offset_factor;
            }
        }

        bool Hue::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            HueEffectConfig config = HueEffectConfig_init_zero;

            float_functions::IFloatFunction *offset_factor;

            config.offset_factor.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.offset_factor.arg = &offset_factor;

            if (!pb_decode(stream, HueEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new Hue(offset_factor);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render