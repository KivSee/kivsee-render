#ifndef __LINEAR_FLOAT_FUNC_H__
#define __LINEAR_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <kivsee/proto/render/v1/functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class Linear : public IFloatFunction
            {
            public:

                float GetValue(float relTime) const override
                {
                    return start_value + relTime * diff_end_to_start;
                }

                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg) {
                    Linear *t = new Linear();
                    kivsee_proto_render_v1_LinearFloatFunctionConfig config = kivsee_proto_render_v1_LinearFloatFunctionConfig_init_zero;
                    if(!pb_decode(stream, kivsee_proto_render_v1_LinearFloatFunctionConfig_fields, &config)) {
                        delete t;
                        return false;
                    }

                    t->start_value = config.start;
                    t->diff_end_to_start = config.end - config.start;
                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float start_value = 0.0;
                float diff_end_to_start = 1.0;
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __LINEAR_FLOAT_FUNC_H__