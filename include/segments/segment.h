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

        typedef std::vector<HSV *> Indices;
        typedef std::pair<char[SEGMENT_NAME_MAX_LENGTH], Indices> Segment;
    }
}

#endif // __SEGMENTS_SEGMENT_H__
