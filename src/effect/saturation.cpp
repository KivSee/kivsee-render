#include <effect/saturation.h>
#include <kivsee/proto/render/v1/effects.pb.h>

namespace kivsee_render
{
    namespace effect
    {
        void Saturation::Render(float rel_time, int cycle_index)
        {
            const float curr_mult_factor = mult_factor->GetValue(rel_time);

            for (::kivsee_render::segments::SegmentPixels::const_iterator it = segment_pixels->begin(); it != segment_pixels->end(); ++it)
            {
                HSV *pixel = it->pixel;
                pixel->sat *= curr_mult_factor;
            }
        }

        bool Saturation::InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            kivsee_proto_render_v1_SaturationEffectConfig config = kivsee_proto_render_v1_SaturationEffectConfig_init_zero;

            float_functions::IFloatFunction *mult_factor;

            config.mult_factor.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
            config.mult_factor.arg = &mult_factor;

            if (!pb_decode(stream, kivsee_proto_render_v1_SaturationEffectConfig_fields, &config))
            {
                return false;
            }
            *((Effect **)*arg) = new Saturation(mult_factor);
            return true;
        }

    } // namespace effect
} // namespace kivsee_render