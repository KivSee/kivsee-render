#ifndef __REPEAT_FLOAT_FUNC_H__
#define __REPEAT_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <kivsee/proto/render/v1/functions.pb.h>
#include <math.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class Repeat : public IFloatFunction
            {
            public:
                float GetValue(float relTime) const override
                {
                    double positionInStep = fmod((relTime * numberOfTimes), 1.0f);
                    return funcToRepeat->GetValue(positionInStep);
                }

                float numberOfTimes;
                IFloatFunction *funcToRepeat;

                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    Repeat *t = new Repeat();

                    kivsee_proto_render_v1_RepeatFloatFunctionConfig config = kivsee_proto_render_v1_RepeatFloatFunctionConfig_init_zero;
                    config.funcToRepeat.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.funcToRepeat.arg = &(t->funcToRepeat);

                    if (!pb_decode(stream, kivsee_proto_render_v1_RepeatFloatFunctionConfig_fields, &config))
                    {
                        delete t;
                        return false;
                    }
                    t->numberOfTimes = config.numberOfTimes;
                    IFloatFunction **f = (IFloatFunction **)(*arg);

                    *f = t;
                    return true;
                }

                ~Repeat()
                {
                    delete funcToRepeat;
                    funcToRepeat = nullptr;
                }
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __REPEAT_FLOAT_FUNC_H__