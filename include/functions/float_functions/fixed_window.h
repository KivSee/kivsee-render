#ifndef __FIXED_WINDOW_FLOAT_FUNC_H__
#define __FIXED_WINDOW_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <kivsee/proto/render/v1/functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            // A window whose ends stay fixed. Applies func only between start and end, renormalized to 0-1 there; outside it returns outside_value.
            // With cyclic, the input wraps around 1 like a cyclic snake, so start 0.75 and end 1.25 cover 0.75-1 and 0-0.25.
            class FixedWindow : public IFloatFunction
            {
            public:
                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    FixedWindow *t = new FixedWindow();
                    kivsee_proto_render_v1_FixedWindowFloatFunctionConfig config = kivsee_proto_render_v1_FixedWindowFloatFunctionConfig_init_zero;
                    config.func.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.func.arg = &(t->func);

                    if (!pb_decode(stream, kivsee_proto_render_v1_FixedWindowFloatFunctionConfig_fields, &config) || t->func == NULL)
                    {
                        delete t;
                        return false;
                    }
                    t->start = config.start;
                    t->end = config.end;
                    t->cyclic = config.cyclic;
                    t->outside_value = config.outside_value;

                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    const float length = end - start;
                    if (length <= 0.0f)
                        return outside_value;

                    float x = rel_time;
                    if (cyclic)
                    {
                        // move x by whole cycles into [start, start + 1), so values past 1 wrap back to 0 and the
                        // position inside the window is still measured from start
                        const float from_start = x - start;
                        x = start + (from_start - floorf(from_start));
                    }

                    if (x < start || x > end)
                        return outside_value;

                    return func->GetValue((x - start) / length);
                }

                float start, end, outside_value;
                bool cyclic;
                IFloatFunction *func = NULL;

                ~FixedWindow()
                {
                    delete func;
                    func = NULL;
                }
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __FIXED_WINDOW_FLOAT_FUNC_H__
