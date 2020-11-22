#ifndef __RAINBOW_COLOR_H__
#define __RAINBOW_COLOR_H__

#include <hsv.h>
#include <effect.h>
#include <pb_decode.h>
#include <effects.pb.h>
#include <functions/float_functions/float_functions.h>

namespace float_functions = kivsee_render::functions::float_functions;

namespace kivsee_render
{
    namespace color
    {

        class Rainbow : public Effect
        {
        public:

            void InitFromPb(pb_istream_t *stream) {
                RainbowEffectConfig config = RainbowEffectConfig_init_zero;

                config.hue_start.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
                config.hue_start.arg = &(this->hue_start);
                config.hue_end.funcs.decode = &float_functions::DecodeFloatFunctionFromStream;
                config.hue_end.arg = &this->hue_end;

                if(!pb_decode(stream, RainbowEffectConfig_fields, &config))
                {
                }
            }

            void Render(float rel_time, int cycle_index) override;

            ~Rainbow() {
                delete hue_start;
                hue_start = nullptr;
                delete hue_end;
                hue_end = nullptr;
            }

        private:
            const float_functions::IFloatFunction *hue_start = nullptr;
            const float_functions::IFloatFunction *hue_end = nullptr;
        };

    } // namespace color
} // namespace kivsee_render

#endif // __RAINBOW_COLOR_H__