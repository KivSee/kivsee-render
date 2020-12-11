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
            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            void Render(float rel_time, int cycle_index) override;

            Rainbow(
                float_functions::IFloatFunction *hue_start,
                float_functions::IFloatFunction *hue_end) : hue_start(hue_start), hue_end(hue_end) {}

            ~Rainbow()
            {
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