#ifndef __I_FLOAT_FUNC_H__
#define __I_FLOAT_FUNC_H__

#include <kivsee/proto/render/v1/functions.pb.h>
#include "pb_decode.h"
#include <math.h>
#include "esp_heap_caps.h"

namespace kivsee_render
{
    namespace functions
    {
        namespace float_functions
        {

            class IFloatFunction
            {

            public:
                virtual ~IFloatFunction() {}

                // Small but numerous: a single effect (e.g. SnakeHue) can decode
                // several of these (head, tail_length, offset_factor, ...), so at
                // thousands of effects this is a major internal-RAM consumer if left
                // on the default allocator. Route to PSRAM like Effect (see effect.h).
                static void *operator new(size_t size)
                {
                    void *p = heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
                    return p ? p : ::operator new(size);
                }

                static void operator delete(void *p)
                {
                    heap_caps_free(p);
                }

            public:
                virtual float GetValue(float relTime) const = 0;
            };

            bool DecodeFloatFunctionFromStream(pb_istream_t *stream, const pb_field_t *field, void **arg);

        } // namespace float
    }     // namespace functions
} // namespace kivsee_render

#endif // __I_FLOAT_FUNC_H__
