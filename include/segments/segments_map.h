#ifndef __SEGMENTS_MAP_H__
#define __SEGMENTS_MAP_H__

#include <list>
#include "segments/segment.h"
#include "pb_decode.h"

namespace kivsee_render
{
    namespace segments
    {
        /**
     * The segments map is a mapping from segment name (string),
     * to a vector of LED indices.
     */
        class SegmentsMap
        {

        public:
            // kivsee_render::HSV leds[NUM_LEDS];

            typedef std::list<Segment> SegmentsList;
            SegmentsList segments;

            uint32_t guid;
            uint32_t number_of_pixels;
        };

        typedef struct SegmentsMapDecodeArgs {
            SegmentsMap** out_segments_map;
            HSV* leds_array;
        };

        bool DecodeSegmentsMapFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg);

    } // namespace segments
} // namespace kivsee_render

#endif // __SEGMENTS_MAP_H__