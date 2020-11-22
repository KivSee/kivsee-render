#ifndef __HALF_FLOAT_FUNC_H__
#define __HALF_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class Half : public IFloatFunction
            {
            public:
                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    Half *t = new Half();
                    HalfFloatFunctionConfig config = HalfFloatFunctionConfig_init_zero;
                    config.f1.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.f1.arg = &(t->f1);
                    config.f2.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.f2.arg = &(t->f2);

                    if (!pb_decode(stream, HalfFloatFunctionConfig_fields, &config))
                    {
                        delete t;
                        return false;
                    }

                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    if (rel_time < 0.5f)
                        return f1->GetValue(rel_time * 2.0f);
                    else
                        return f2->GetValue((rel_time - 0.5f) * 2.0f);
                }

                IFloatFunction *f1, *f2;

                ~Half()
                {
                    delete f1;
                    f1 = NULL;
                    delete f2;
                    f2 = NULL;
                }
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __HALF_FLOAT_FUNC_H__
