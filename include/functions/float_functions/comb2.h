#ifndef __COMB_2_FLOAT_FUNC_H__
#define __COMB_2_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class Comb2 : public IFloatFunction
            {
            public:
                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    Comb2 *t = new Comb2();
                    Comb2FloatFunctionConfig config = Comb2FloatFunctionConfig_init_zero;
                    config.f1.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.f1.arg = &(t->f1);
                    config.f2.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.f2.arg = &(t->f2);

                    if (!pb_decode(stream, Comb2FloatFunctionConfig_fields, &config))
                    {
                        delete t;
                        return false;
                    }
                    t->amount1 = config.amount1;
                    t->amount2 = config.amount2;

                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    return (amount1 * f1->GetValue(rel_time)) + (amount2 * f2->GetValue(rel_time));
                }

                float amount1, amount2;
                IFloatFunction *f1, *f2;

                ~Comb2()
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

#endif // __COMB_2_FLOAT_FUNC_H__