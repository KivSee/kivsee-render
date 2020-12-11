#include <color/const_color.h>
#include <effects.pb.h>

namespace kivsee_render
{
    namespace color
    {
        void ConstColor::Render(float rel_time, int cycle_index)
        {
            for (std::vector<HSV *>::const_iterator it = pixels->begin(); it != pixels->end(); ++it)
            {
                HSV *pixel = *it;
                pixel->hue = color.hue;
                pixel->sat = color.sat;
                pixel->val = color.val;
            }
        }

        bool ConstColor::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            ConstColorEffectConfig config = ConstColorEffectConfig_init_zero;

            bool success = pb_decode(stream, ConstColorEffectConfig_fields, &config);
            if(!success) return false;
            *((ConstColor **)*arg) = new ConstColor(HSV{config.color.hue, config.color.sat, config.color.val});

            return true;
        }

    } // namespace color
} // namespace kivsee_render