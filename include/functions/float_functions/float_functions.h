#ifndef __I_FLOAT_FUNC_H__
#define __I_FLOAT_FUNC_H__

#include <kivsee/proto/render/v1/functions.pb.h>
#include "pb_decode.h"
#include <math.h>

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

            public:
                virtual float GetValue(float relTime) const = 0;
            };

            bool DecodeFloatFunctionFromStream(pb_istream_t *stream, const pb_field_t *field, void **arg);

        } // namespace float
    }     // namespace functions
} // namespace kivsee_render

#endif // __I_FLOAT_FUNC_H__
