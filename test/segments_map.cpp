#include "gtest/gtest.h"

#include "segments/segments_map.h"
#include "hsv.h"
#include "segments.pb.h"

TEST(SegmentsMap, SingleSegment)
{

  // create configuration with single segment
  ::kivsee::proto::ThingSegments thingSegments;
  thingSegments.set_guid(1234);
  thingSegments.set_number_of_pixels(50);
  ::kivsee::proto::Segment *singleSegment = thingSegments.add_segments();
  singleSegment->set_name("from_test");
  
  ::kivsee::proto::Pixel *p1 = singleSegment->add_pixels();
  p1->set_index(17);
  p1->set_rel_pos(0.0);
  ::kivsee::proto::Pixel *p2 = singleSegment->add_pixels();
  p2->set_index(9);
  p2->set_rel_pos(0.5);
  ::kivsee::proto::Pixel *p3 = singleSegment->add_pixels();
  p3->set_index(34);
  p3->set_rel_pos(1.0);

  // encode it to buffer to feed into nanopb
  size_t size = thingSegments.ByteSizeLong(); 
  uint8_t *msgBuffer = new uint8_t[size];
  thingSegments.SerializeToArray(msgBuffer, size);

  // data structures to use during segments map construction
  kivsee_render::segments::SegmentsMap *segments_map = nullptr;
  kivsee_render::HSV leds[50];

  // define the decoder
  pb_istream_t segments_map_stream = pb_istream_from_buffer(msgBuffer, size);
  ::kivsee_render::segments::SegmentsMapDecodeArgs segments_map_decode_args;
  segments_map_decode_args.out_segments_map = &segments_map;
  segments_map_decode_args.leds_array = leds;
  void *arg = &segments_map_decode_args;

  // decode
  bool decodeSuccess = ::kivsee_render::segments::DecodeSegmentsMapFromPbStream(&segments_map_stream, nullptr, &arg);
  ASSERT_TRUE(decodeSuccess);

  // check that segments_map initialized correectly according to message  
  ::kivsee_render::segments::SegmentPixels *segmentPixels = segments_map->getPixelsForSegment("from_test");
  ASSERT_EQ(segmentPixels->size(), 3);
  ASSERT_EQ((*segmentPixels)[0].pixel, leds + 17);
  ASSERT_EQ((*segmentPixels)[0].relativePositionInSegment, 0.0);
  ASSERT_EQ((*segmentPixels)[1].pixel, leds + 9);
  ASSERT_EQ((*segmentPixels)[1].relativePositionInSegment, 0.5);
  ASSERT_EQ((*segmentPixels)[2].pixel, leds + 34);
  ASSERT_EQ((*segmentPixels)[2].relativePositionInSegment, 1.0);

  // check negative case
  ASSERT_EQ(segments_map->getPixelsForSegment("invalid"), nullptr);

  // cleanup
  delete msgBuffer;
}

TEST(SegmentsMap, SegmentWithNoPixels)
{
  ::kivsee::proto::ThingSegments thingSegments;
  thingSegments.set_guid(1234);
  thingSegments.set_number_of_pixels(50);
  ::kivsee::proto::Segment *emptySegment = thingSegments.add_segments();
  emptySegment->set_name("from_test");
  ::kivsee::proto::Segment *nonEmptySegment = thingSegments.add_segments();
  nonEmptySegment->set_name("nonempty");
  ::kivsee::proto::Pixel *p1 = nonEmptySegment->add_pixels();
  p1->set_index(17);
  p1->set_rel_pos(0.0);

  // encode it to buffer to refeed into nanopb
  size_t size = thingSegments.ByteSizeLong(); 
  uint8_t *msgBuffer = new uint8_t[size];
  thingSegments.SerializeToArray(msgBuffer, size);

  // data structures to use during segments map construction
  kivsee_render::segments::SegmentsMap *segments_map = nullptr;
  kivsee_render::HSV leds[50];

  // define the decoder
  pb_istream_t segments_map_stream = pb_istream_from_buffer(msgBuffer, size);
  ::kivsee_render::segments::SegmentsMapDecodeArgs segments_map_decode_args;
  segments_map_decode_args.out_segments_map = &segments_map;
  segments_map_decode_args.leds_array = leds;
  void *arg = &segments_map_decode_args;

  // decode
  bool decodeSuccess = ::kivsee_render::segments::DecodeSegmentsMapFromPbStream(&segments_map_stream, nullptr, &arg);
  ASSERT_TRUE(decodeSuccess);

  ::kivsee_render::segments::SegmentPixels *pixelsEmpty = segments_map->getPixelsForSegment("from_test");
  ASSERT_EQ(pixelsEmpty->size(), 0);

  ::kivsee_render::segments::SegmentPixels *pixelsNonEmpty = segments_map->getPixelsForSegment("nonempty");
  ASSERT_EQ(pixelsNonEmpty->size(), 1);
  

  // cleanup
  delete msgBuffer;
}
