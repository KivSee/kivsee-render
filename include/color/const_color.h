#ifndef __COLOR_CONST_COLOR_H__
#define __COLOR_CONST_COLOR_H__

#include <hsv.h>
#include <effect.h>
#include <effects.pb.h>

namespace kivsee_render
{
    namespace color
    {

        class ConstColor : public Effect
        {
        public:

            ConstColor(const ConstColorEffectConfig &config): config(config) {}

            void Render(float rel_time, int cycle_index) override;

        private:
            ConstColorEffectConfig config;
        };

    } // namespace color
} // namespace kivsee_render

#endif // __COLOR_CONST_COLOR_H__