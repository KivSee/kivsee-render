#include <functions/float_functions/float_functions.h>

#include <functions/float_functions/const_value.h>
#include <functions/float_functions/linear.h>
#include <functions/float_functions/sin.h>
#include <functions/float_functions/steps.h>
#include <functions/float_functions/repeat.h>
#include <functions/float_functions/half.h>
#include <functions/float_functions/comb2.h>


namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {
            bool DecodeFloatFunctionFromStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {

                IFloatFunction **dest = (IFloatFunction **)(*arg);
                kivsee_proto_render_v1_FloatFunction config = kivsee_proto_render_v1_FloatFunction_init_zero;

                config.const_value.funcs.decode = &ConstValue::InitFromPb;
                config.const_value.arg = dest;

                config.linear.funcs.decode = &Linear::InitFromPb;
                config.linear.arg = dest;

                config.sin.funcs.decode = &Sin::InitFromPb;
                config.sin.arg = dest;

                config.steps.funcs.decode = &Steps::InitFromPb;
                config.steps.arg = dest;

                config.repeat.funcs.decode = &Repeat::InitFromPb;
                config.repeat.arg = dest;

                config.half.funcs.decode = &Half::InitFromPb;
                config.half.arg = dest;

                config.comb2.funcs.decode = &Comb2::InitFromPb;
                config.comb2.arg = dest;

                if(!pb_decode(stream, kivsee_proto_render_v1_FloatFunction_fields, &config)) 
                    return false;

                if(*dest == nullptr)
                    return false;

                return true;
            }

        } // namespace float
    }     // namespace functions
} // namespace kivsee_render

