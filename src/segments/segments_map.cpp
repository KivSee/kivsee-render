#include "segments/segments_map.h"

#include "segments.pb.h"

namespace kivsee_render {
    namespace segments {

        struct DecodeSegmentIndexArgs {
            Pixels *pixels;
            kivsee_render::HSV *leds;
        };

        bool DecodeSegmentIndexFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {
            DecodeSegmentIndexArgs *decodeSegmentIndexArgs = (DecodeSegmentIndexArgs *) *arg;

            uint32_t index;
            if (!pb_decode_varint32(stream, &index))
                return false;

            decodeSegmentIndexArgs->pixels->push_back(decodeSegmentIndexArgs->leds + index);
            return true;
        }

        struct DecodeSegmentArgs {
            SegmentsMap *segments_map;
            kivsee_render::HSV *leds;
        };

        bool DecodeSegmentFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {
            DecodeSegmentArgs *decodeSegmentArgs = (DecodeSegmentArgs *) *arg;
            
            Segment segment;

            SegmentConfig segment_config = SegmentConfig_init_zero;
            segment_config.indices.funcs.decode = &DecodeSegmentIndexFromPbStream;
            DecodeSegmentIndexArgs decodeSegmentIndexArgs {
                &segment.second,
                decodeSegmentArgs->leds,
            };
            segment_config.indices.arg = &decodeSegmentIndexArgs;

            bool success = pb_decode(stream, SegmentConfig_fields, &segment_config);
            if(!success) return false;

            strncpy(segment.first, segment_config.name, SEGMENT_NAME_MAX_LENGTH);
            segment.first[SEGMENT_NAME_MAX_LENGTH - 1] = '\0';

            decodeSegmentArgs->segments_map->segments.push_back(segment);

            return true;
        }

        bool DecodeSegmentsMapFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {

            SegmentsMapDecodeArgs *segmentsMapArgs = (SegmentsMapDecodeArgs *) *arg;
            HSV *ledsArray = segmentsMapArgs->leds_array;

            SegmentsMap *segments_map = new SegmentsMap();

            SegmentsMapConfig segments_map_pb = SegmentsMapConfig_init_zero;
            segments_map_pb.segments.funcs.decode = &DecodeSegmentFromPbStream;
            DecodeSegmentArgs args {
                segments_map,
                ledsArray
            };
            segments_map_pb.segments.arg = &args;

            bool success = pb_decode(stream, SegmentsMapConfig_fields, &segments_map_pb);
            if(!success) return false;

            segments_map->guid = segments_map_pb.guid;
            segments_map->number_of_pixels = segments_map_pb.number_of_pixels;

            Segment segment;
            strncpy(segment.first, "all", 4);
            for(int i=0; i<segments_map->number_of_pixels; i++) {
                segment.second.push_back(&ledsArray[i]);
            }
            segments_map->segments.push_back(segment);

            *((*( (SegmentsMapDecodeArgs **) arg))->out_segments_map) = segments_map;

            return true;
        }

    }
}