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
     * to a vector of LED pixels.
     */
        class SegmentsMap
        {

        public:

            SegmentPixels *getPixelsForSegment(const char *segmentName) {
                for(std::list<Segment>::iterator it = segments.begin(); it != segments.end(); it++) {
                    if(strcmp(it->first, segmentName) == 0) {
                        return &(it->second);
                    }
                }
                return nullptr;
            }

            typedef std::list<Segment> SegmentsList;
            SegmentsList segments;

            uint32_t guid;
            uint32_t number_of_pixels;
        };

        typedef struct SegmentsMapDecodeArgs {
            SegmentsMap** out_segments_map;
            HSV* leds_array;
        } SegmentsMapDecodeArgs;

        bool DecodeSegmentsMapFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg);
        uint16_t GetNumberOfPixels(pb_istream_t *stream, const pb_field_t *field, void **arg);

    } // namespace segments
} // namespace kivsee_render

#endif // __SEGMENTS_MAP_H__