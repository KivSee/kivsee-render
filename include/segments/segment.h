#ifndef __SEGMENTS_SEGMENT_H__
#define __SEGMENTS_SEGMENT_H__

#include <vector>
#include "hsv.h"

namespace kivsee_render {
    namespace segments {

        // this value is also defined in the proto file for segments.proto.
        // if changed here or there, the change should be reflected to the 
        // other location so they are aligned
        const int SEGMENT_NAME_MAX_LENGTH = 10;

        typedef struct {

            // pixel is a pointer to the actual value.
            // changing this HSV will affect the final buffer which is rendered
            HSV *pixel;

            // This value is the relative position of the pixel within the segment
            float relativePositionInSegment;
        } SegmentPixel;

        typedef std::vector<SegmentPixel> SegmentPixels;
        typedef std::pair<char[SEGMENT_NAME_MAX_LENGTH], SegmentPixels> Segment;
    }
}

#endif // __SEGMENTS_SEGMENT_H__
