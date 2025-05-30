#include "segments/segments_map.h"

#include <kivsee/proto/render/v1/segments.pb.h>

namespace kivsee_render {
    namespace segments {

        struct DecodeSegmentPixelArgs {
            SegmentPixels *segmentPixels;
            kivsee_render::HSV *leds;
        };

        bool DecodeSegmentPixelFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {
            DecodeSegmentPixelArgs *decodeSegmentIndexArgs = (DecodeSegmentPixelArgs *) *arg;

            kivsee_proto_render_v1_Pixel pixel = kivsee_proto_render_v1_Pixel_init_zero;
            if(!pb_decode(stream, kivsee_proto_render_v1_Pixel_fields, &pixel)) {
                return false;
            }

            SegmentPixel segmentPixel;
            segmentPixel.pixel = decodeSegmentIndexArgs->leds + pixel.index;
            segmentPixel.relativePositionInSegment = pixel.rel_pos;
            decodeSegmentIndexArgs->segmentPixels->push_back(segmentPixel);
            return true;
        }

        struct DecodeSegmentArgs {
            SegmentsMap *segments_map;
            kivsee_render::HSV *leds;
        };

        bool DecodeSegmentFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {
            DecodeSegmentArgs *decodeSegmentArgs = (DecodeSegmentArgs *) *arg;
            
            Segment segment;

            kivsee_proto_render_v1_Segment segment_config = kivsee_proto_render_v1_Segment_init_zero;
            segment_config.pixels.funcs.decode = &DecodeSegmentPixelFromPbStream;
            DecodeSegmentPixelArgs decodeSegmentIndexArgs {
                &segment.second,
                decodeSegmentArgs->leds,
            };
            segment_config.pixels.arg = &decodeSegmentIndexArgs;

            bool success = pb_decode(stream,  kivsee_proto_render_v1_Segment_fields, &segment_config);
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

            kivsee_proto_render_v1_ThingSegments segments_map_pb = kivsee_proto_render_v1_ThingSegments_init_zero;
            segments_map_pb.segments.funcs.decode = &DecodeSegmentFromPbStream;
            DecodeSegmentArgs args {
                segments_map,
                ledsArray
            };
            segments_map_pb.segments.arg = &args;

            bool success = pb_decode(stream, kivsee_proto_render_v1_ThingSegments_fields, &segments_map_pb);
            if(!success) return false;

            segments_map->guid = segments_map_pb.guid;
            segments_map->number_of_pixels = segments_map_pb.number_of_pixels;

            // Segment segment;
            // strncpy(segment.first, "all", 4);
            // for(int i=0; i<segments_map->number_of_pixels; i++) {
            //     segment.second.push_back(&ledsArray[i]);
            // }
            // segments_map->segments.push_back(segment);

            *((*( (SegmentsMapDecodeArgs **) arg))->out_segments_map) = segments_map;

            return true;
        }

        uint16_t GetNumberOfPixels(pb_istream_t *stream, const pb_field_t *field, void **arg) {
            kivsee_proto_render_v1_ThingSegments segments_map_pb = kivsee_proto_render_v1_ThingSegments_init_zero;
            bool success = pb_decode(stream, kivsee_proto_render_v1_ThingSegments_fields, &segments_map_pb);
            if(!success) return 0;
            return segments_map_pb.number_of_pixels;
        }

    }
}