#include <color/rainbow.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace color
    {
        void Rainbow::Render(float rel_time, int cycle_index)
        {
            const float curr_start_hue = hue_start->GetValue(rel_time);
            const float curr_end_hue = hue_end->GetValue(rel_time);
            const float curr_hue_diff = curr_end_hue - curr_start_hue;

            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                float rel_pos = it->relativePositionInSegment;
                pixel->hue = curr_start_hue + curr_hue_diff * rel_pos;
                pixel->sat = 1.0f;
                pixel->val = 1.0f;
            }
        }

        bool Rainbow::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_RainbowEffectConfig config = kivsee_proto_render_v1_RainbowEffectConfig_init_zero;

            float_functions::IFloatFunction *hue_start;
            float_functions::IFloatFunction *hue_end;

            config.hue_start.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.hue_start.arg = &hue_start;
            config.hue_end.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.hue_end.arg = &hue_end;

            if (!pb_decode(stream, kivsee_proto_render_v1_RainbowEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new Rainbow(hue_start, hue_end);
            return true;
        }

    } // namespace color
} // namespace kivsee_render