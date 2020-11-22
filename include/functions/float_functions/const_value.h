#ifndef __CONST_VALUE_FLOAT_FUNC_H__
#define __CONST_VALUE_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <functions.pb.h>

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
                    ConstValueFloatFunctionConfig config = ConstValueFloatFunctionConfig_init_zero;
                    if(!pb_decode(stream, ConstValueFloatFunctionConfig_fields, &config)) {
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