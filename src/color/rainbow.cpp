#include <color/rainbow.h>

namespace kivsee_render
{
    namespace color
    {

        void Rainbow::Render(float rel_time, int cycle_index)
        {
            const float curr_start_hue = hue_start->GetValue(rel_time);
            const float curr_end_hue = hue_end->GetValue(rel_time);
            const float curr_hue_diff = curr_end_hue - curr_start_hue;

            float numberOfPixels = (float)pixels->size();
            for (int i = 0; i < pixels->size(); i++)
            {
                HSV *pixel = (*pixels)[i];
                float rel_pos = ((float)i / numberOfPixels);
                pixel->hue = curr_start_hue + curr_hue_diff * rel_pos;
                pixel->sat = 1.0f;
                pixel->val = 1.0f;
            }
        }

    } // namespace color
} // namespace kivsee_render