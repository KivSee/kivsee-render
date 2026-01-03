#ifndef __EFFECT_TIMED_SATURATION_H__
#define __EFFECT_TIMED_SATURATION_H__

#include <hsv.h>
#include "pb_decode.h"
#include <effect.h>
#include <kivsee/proto/render/v1/effects.pb.h>
#include <functions/float_functions/float_functions.h>

namespace float_functions = kivsee_render::functions::float_functions;

namespace kivsee_render
{
    namespace effect
    {

        class TimedSaturation : public Effect
        {
        public:

            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            TimedSaturation(float_functions::IFloatFunction *mult_factor_increase, float_functions::IFloatFunction *mult_factor_decrease): mult_factor_increase(mult_factor_increase), mult_factor_decrease(mult_factor_decrease) {}

            ~TimedSaturation()
            {
                delete mult_factor_increase;
                mult_factor_increase = nullptr;
                delete mult_factor_decrease;
                mult_factor_decrease = nullptr;
            }

            void Render(float rel_time, int cycle_index) override;

        private:
            const float_functions::IFloatFunction *mult_factor_increase = nullptr;
            const float_functions::IFloatFunction *mult_factor_decrease = nullptr;
        };

    } // namespace effect
} // namespace kivsee_render

#endif // __EFFECT_TIMED_SATURATION_H__

