#ifndef __CONST_VALUE_FLOAT_FUNC_H__
#define __CONST_VALUE_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <kivsee/proto/render/v1/functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class ConstValue : public IFloatFunction
            {
            public:

                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg) {
                    ConstValue *t = new ConstValue();
                    kivsee_proto_render_v1_ConstValueFloatFunctionConfig config = kivsee_proto_render_v1_ConstValueFloatFunctionConfig_init_zero;
                    if(!pb_decode(stream, kivsee_proto_render_v1_ConstValueFloatFunctionConfig_fields, &config)) {
                        delete t;
                        return false;
                    }

                    t->value = config.value;
                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    return value;
                }

                float value = 0.0;
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __CONST_VALUE_FLOAT_FUNC_H__