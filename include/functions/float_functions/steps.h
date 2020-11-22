#ifndef __STEPS_FLOAT_FUNC_H__
#define __STEPS_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class Steps : public IFloatFunction
            {

            public:
                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    Steps *t = new Steps();
                    StepsFloatFunctionConfig config = StepsFloatFunctionConfig_init_zero;
                    if (!pb_decode(stream, StepsFloatFunctionConfig_fields, &config))
                    {
                        delete t;
                        return false;
                    }

                    t->num_steps = config.num_steps;
                    t->diff_per_step = config.diff_per_step;
                    t->first_step_value = config.first_step_value;
                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    int curr_step = (int)(rel_time * num_steps);
                    return first_step_value + diff_per_step * curr_step;
                }

                int num_steps;
                float diff_per_step;
                float first_step_value;
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __STEPS_FLOAT_FUNC_H__
