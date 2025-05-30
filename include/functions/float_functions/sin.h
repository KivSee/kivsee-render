#ifndef __SIN_FLOAT_FUNC_H__
#define __SIN_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <kivsee/proto/render/v1/functions.pb.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class Sin : public IFloatFunction
            {
                
            public:
                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    Sin *t = new Sin();
                    kivsee_proto_render_v1_SinFloatFunctionConfig config = kivsee_proto_render_v1_SinFloatFunctionConfig_init_zero;
                    if (!pb_decode(stream, kivsee_proto_render_v1_SinFloatFunctionConfig_fields, &config))
                    {
                        delete t;
                        return false;
                    }

                    t->min_value = config.min;
                    t->max_value = config.max;
                    t->phase = config.phase;
                    t->repeats = config.repeats;
                    t->diff_max_to_min = config.max - config.min;
                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    float angleRad = (rel_time * repeats + phase) * 2.0 * M_PI;
                    float sinResult = sin(angleRad);
                    return ((sinResult + 1.0) / 2.0) * diff_max_to_min + min_value;
                }

                float min_value = 0.0;
                float max_value = 1.0;
                float phase = 0.0;
                float repeats = 1.0;
                float diff_max_to_min = max_value - min_value;
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __SIN_FLOAT_FUNC_H__