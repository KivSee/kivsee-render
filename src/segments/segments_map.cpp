#include "segments/segments_map.h"

#include "segments.pb.h"

namespace kivsee_render {
    namespace segments {

        bool DecodeSegmentIndexFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {
            uint32_t index;
            if (!pb_decode_varint32(stream, &index))
                return false;
            Segment *segment = (Segment *)*arg;
            // segment->push_back(value);
            return true;
        }

        bool DecodeSegmentFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {

            SegmentsMap *segments_map = (SegmentsMap *) *arg;
            
            Segment segment;

            SegmentConfig segment_config = SegmentConfig_init_zero;
            segment_config.indices.funcs.decode = &DecodeSegmentIndexFromPbStream;
            segment_config.indices.arg = &segment.second;

            bool success = pb_decode(stream, SegmentConfig_fields, &segment_config);
            if(!success) return false;

            strncpy(segment.first, segment_config.name, SEGMENT_NAME_MAX_LENGTH);
            segment.first[SEGMENT_NAME_MAX_LENGTH - 1] = '\0';

            segments_map->segments.push_back(segment);

            return true;
        }

        bool DecodeSegmentsMapFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {

            SegmentsMap *segments_map = new SegmentsMap();

            SegmentsMapConfig segments_map_pb = SegmentsMapConfig_init_zero;
            segments_map_pb.segments.funcs.decode = &DecodeSegmentFromPbStream;
            segments_map_pb.segments.arg = segments_map;

            bool success = pb_decode(stream, SegmentsMapConfig_fields, &segments_map_pb);
            if(!success) return false;

            segments_map->guid = segments_map_pb.guid;
            segments_map->number_of_pixels = segments_map_pb.number_of_pixels;

            *((*( (SegmentsMapDecodeArgs **) arg))->out_segments_map) = segments_map;

            return true;
        }

    }
}