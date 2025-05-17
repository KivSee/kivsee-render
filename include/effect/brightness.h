#ifndef __EFFECT_BRIGHTNESS_H__
#define __EFFECT_BRIGHTNESS_H__

#include <hsv.h>
#include "pb_decode.h"
#include <effect.h>
#include <effects.pb.h>
#include <functions/float_functions/float_functions.h>

namespace float_functions = kivsee_render::functions::float_functions;

namespace kivsee_render
{
    namespace effect
    {

        class Brightness : public Effect
        {
        public:

            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            Brightness(float_functions::IFloatFunction *mult_factor): mult_factor(mult_factor) {}

            ~Brightness()
            {
                delete mult_factor;
                mult_factor = nullptr;
            }

            void Render(float rel_time, int cycle_index) override;

        private:
            const float_functions::IFloatFunction *mult_factor = nullptr;
        };

    } // namespace effect
} // namespace kivsee_render

#endif // __EFFECT_BRIGHTNESS_H__