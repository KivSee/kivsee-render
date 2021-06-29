#include "gtest/gtest.h"

#include "segments/segments_map.h"
#include "hsv.h"
#include "segments.pb.h"

TEST(SegmentsMap, SingleSegment)
{

  // create configuration with single segment
  SegmentsMapConfig segmentsMapConfig;
  segmentsMapConfig.set_guid(1234);
  segmentsMapConfig.set_number_of_pixels(50);
  SegmentConfig *singleSegment = segmentsMapConfig.add_segments();
  singleSegment->set_name("from_test");
  singleSegment->add_indices(17);
  singleSegment->add_indices(9);
  singleSegment->add_indices(34);

  // encode it to buffer to feed into nanopb
  size_t size = segmentsMapConfig.ByteSizeLong(); 
  uint8_t *msgBuffer = new uint8_t[size];
  segmentsMapConfig.SerializeToArray(msgBuffer, size);

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
  ::kivsee_render::segments::Pixels *pixels = segments_map->getPixelsForSegment("from_test");
  ASSERT_EQ(pixels->size(), 3);
  ASSERT_EQ((*pixels)[0], leds + 17);
  ASSERT_EQ((*pixels)[1], leds + 9);
  ASSERT_EQ((*pixels)[2], leds + 34);

  // check negative case
  ASSERT_EQ(segments_map->getPixelsForSegment("invalid"), nullptr);

  // cleanup
  delete msgBuffer;
}
