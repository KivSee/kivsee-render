#ifndef __EFFECT_SNAKE_BRIGHTNESS_H__
#define __EFFECT_SNAKE_BRIGHTNESS_H__

#include <utility>
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

        class SnakeBrightness : public Effect
        {
        public:

            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            SnakeBrightness(float_functions::IFloatFunction *head, float_functions::IFloatFunction *tail_length, bool cyclic, float repeat_num, float_functions::IFloatFunction *mult_factor_increase, float_functions::IFloatFunction *mult_factor_decrease): head(head), tail_length(tail_length), cyclic(cyclic), repeat_num(repeat_num), mult_factor_increase(mult_factor_increase), mult_factor_decrease(mult_factor_decrease) {}

            ~SnakeBrightness()
            {
                delete head;
                head = nullptr;
                delete tail_length;
                tail_length = nullptr;
                delete mult_factor_increase;
                mult_factor_increase = nullptr;
                delete mult_factor_decrease;
                mult_factor_decrease = nullptr;
            }

            void Render(float rel_time, int cycle_index) override;

        private:
            void ClearPixels();
            std::pair<float, float> ExtractHeadPixels(float curr_head, float curr_tail_length);

        private:
            const float_functions::IFloatFunction *head = nullptr;
            const float_functions::IFloatFunction *tail_length = nullptr;
            const bool cyclic = false;
            const float repeat_num = 0.0f;
            const float_functions::IFloatFunction *mult_factor_increase = nullptr;
            const float_functions::IFloatFunction *mult_factor_decrease = nullptr;
        };

    } // namespace effect
} // namespace kivsee_render

#endif // __EFFECT_SNAKE_BRIGHTNESS_H__

