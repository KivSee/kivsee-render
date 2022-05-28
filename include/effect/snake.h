#ifndef __EFFECT_SNAKE_H__
#define __EFFECT_SNAKE_H__

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

        class Snake : public Effect
        {
        public:

            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            Snake(float_functions::IFloatFunction *head, float_functions::IFloatFunction *tail_length): head(head), tail_length(tail_length) {}

            ~Snake()
            {
                delete head;
                head = nullptr;
                delete tail_length;
                tail_length = nullptr;
            }

            void Render(float rel_time, int cycle_index) override;

        private:
            const float_functions::IFloatFunction *head = nullptr;
            const float_functions::IFloatFunction *tail_length = nullptr;
        };

    } // namespace effect
} // namespace kivsee_render

#endif // __EFFECT_SNAKE_H__