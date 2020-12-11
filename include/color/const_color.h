#ifndef __COLOR_CONST_COLOR_H__
#define __COLOR_CONST_COLOR_H__

#include <hsv.h>
#include <effect.h>

namespace kivsee_render
{
    namespace color
    {

        class ConstColor : public Effect
        {
        public:

            static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg);

            ConstColor(const HSV &color): color(color) {}

            void Render(float rel_time, int cycle_index) override;

        private:
            HSV color;
        };

    } // namespace color
} // namespace kivsee_render

#endif // __COLOR_CONST_COLOR_H__