#ifndef __EFFECT_SATURATION_H__
#define __EFFECT_SATURATION_H__

#include <hsv.h>
#include <pb_decode.h>
#include <effect.h>
#include <effects.pb.h>
#include <functions/float_functions/float_functions.h>

namespace float_functions = kivsee_render::functions::float_functions;

namespace kivsee_render
{
    namespace effect
    {

        class Saturation : public Effect
        {
        public:

            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            Saturation(float_functions::IFloatFunction *mult_factor): mult_factor(mult_factor) {}

            ~Saturation()
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

#endif // __EFFECT_SATURATION_H__