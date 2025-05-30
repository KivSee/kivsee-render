#include <color/const_color.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace color
    {
        void ConstColor::Render(float rel_time, int cycle_index)
        {
            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                pixel->hue = color.hue;
                pixel->sat = color.sat;
                pixel->val = color.val;
            }
        }

        bool ConstColor::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_ConstColorEffectConfig config = kivsee_proto_render_v1_ConstColorEffectConfig_init_zero;

            bool success = pb_decode(stream, kivsee_proto_render_v1_ConstColorEffectConfig_fields, &config);
            if(!success) return false;
            *((ConstColor **)*arg) = new ConstColor(HSV{config.color.hue, config.color.sat, config.color.val});

            return true;
        }

    } // namespace color
} // namespace kivsee_render