#ifndef __MOVING_WINDOW_FLOAT_FUNC_H__
#define __MOVING_WINDOW_FLOAT_FUNC_H__

#include <functions/float_functions/float_functions.h>
#include <kivsee/proto/render/v1/functions.pb.h>

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            // A window whose ends are float functions, evaluated at the same input. Returns inside_value between start
            // and end and outside_value everywhere else. With cyclic, the input wraps around 1 like a cyclic snake.
            class MovingWindow : public IFloatFunction
            {
            public:
                static bool InitFromPb(pb_istream_t *stream, const pb_field_t *field, void **arg)
                {
                    MovingWindow *t = new MovingWindow();
                    kivsee_proto_render_v1_MovingWindowFloatFunctionConfig config = kivsee_proto_render_v1_MovingWindowFloatFunctionConfig_init_zero;
                    config.start.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.start.arg = &(t->start);
                    config.end.funcs.decode = &DecodeFloatFunctionFromStream;
                    config.end.arg = &(t->end);

                    if (!pb_decode(stream, kivsee_proto_render_v1_MovingWindowFloatFunctionConfig_fields, &config) || t->start == NULL || t->end == NULL)
                    {
                        delete t;
                        return false;
                    }
                    t->inside_value = config.inside_value;
                    t->outside_value = config.outside_value;
                    t->cyclic = config.cyclic;

                    *((IFloatFunction **)*arg) = t;
                    return true;
                }

                float GetValue(float rel_time) const override
                {
                    const float curr_start = start->GetValue(rel_time);
                    const float curr_end = end->GetValue(rel_time);
                    if (curr_end < curr_start)
                        return outside_value;

                    float x = rel_time;
                    if (cyclic)
                    {
                        // move x by whole cycles into [start, start + 1), so values past 1 wrap back to 0
                        const float from_start = x - curr_start;
                        x = curr_start + (from_start - floorf(from_start));
                    }

                    return (x >= curr_start && x <= curr_end) ? inside_value : outside_value;
                }

                float inside_value, outside_value;
                bool cyclic;
                IFloatFunction *start = NULL, *end = NULL;

                ~MovingWindow()
                {
                    delete start;
                    start = NULL;
                    delete end;
                    end = NULL;
                }
            };

        } // namespace float_functions
    }     // namespace functions
} // namespace kivsee_render

#endif // __MOVING_WINDOW_FLOAT_FUNC_H__
