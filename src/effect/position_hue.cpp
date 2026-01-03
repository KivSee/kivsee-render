#include <effect/position_hue.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        void PositionHue::Render(float rel_time, int cycle_index)
        {
            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                float rel_pos = it->relativePositionInSegment;
                const float curr_offset_factor = offset_factor->GetValue(rel_pos);
                pixel->hue += curr_offset_factor;
            }
        }

        bool PositionHue::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_PositionHueEffectConfig config = kivsee_proto_render_v1_PositionHueEffectConfig_init_zero;

            float_functions::IFloatFunction *offset_factor;

            config.offset_factor.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.offset_factor.arg = &offset_factor;

            if (!pb_decode(stream, kivsee_proto_render_v1_PositionHueEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new PositionHue(offset_factor);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render

