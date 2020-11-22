#include <color/const_color.h>

namespace kivsee_render
{
    namespace color
    {

        void ConstColor::Render(float rel_time, int cycle_index)
        {
            for (std::vector<HSV *>::const_iterator it = pixels->begin(); it != pixels->end(); ++it)
            {
                HSV *pixel = *it;
                pixel->hue = config.color.h;
                pixel->sat = config.color.s;
                pixel->val = config.color.v;
            }
        }

    } // namespace color
} // namespace kivsee_render