#include "gtest/gtest.h"

#include "effects.pb.h"
#include "effect.h"
#include "hsv.h"

EffectProto testConstColorEffect(const char *segmentName) {
    EffectProto effectProto;
    effectProto.mutable_effect_config()->set_start_time(0);
    effectProto.mutable_effect_config()->set_end_time(100);
    effectProto.mutable_effect_config()->set_segments(segmentName);

    effectProto.mutable_const_color()->mutable_color()->set_hue(0.5);
    effectProto.mutable_const_color()->mutable_color()->set_sat(0.25);
    effectProto.mutable_const_color()->mutable_color()->set_val(1.0);
    return effectProto;
}

pb_istream_t createPbStreamSingleEffect(const char *segmentName) {
    EffectProto effectProto = testConstColorEffect(segmentName);
    size_t size = effectProto.ByteSizeLong();
    uint8_t *msgBuffer = new uint8_t[size];
    effectProto.SerializeToArray(msgBuffer, size);
    return pb_istream_from_buffer(msgBuffer, size);
}

void assertRenderedPixel(kivsee_render::HSV *pixel) {
    ASSERT_EQ(pixel->hue, 0.5);
    ASSERT_EQ(pixel->sat, 0.25);
    ASSERT_EQ(pixel->val, 1.0);
}

TEST(EffectSegments, SegmentFoundInStore)
{
    pb_istream_t effect_stream = createPbStreamSingleEffect("seg");

    // segment store for test
    kivsee_render::HSV leds[3];
    kivsee_render::segments::SegmentsMap segmentsMap;
    kivsee_render::segments::Segment segment;
    strcpy(segment.first, "seg");
    segment.second.push_back({&leds[1], 0.0});
    segmentsMap.segments.push_back(segment);

    // decode args
    kivsee_render::DecodeEffectArgs decodeEffectArgs;
    decodeEffectArgs.segmentsMap = &segmentsMap;
    decodeEffectArgs.effects = new std::list<kivsee_render::Effect *>();
    void *arg = &decodeEffectArgs;

    bool decodeSuccess = ::kivsee_render::DecodeEffectFromPbStream(&effect_stream, nullptr, &arg);
    ASSERT_TRUE(decodeSuccess);
    ASSERT_EQ(decodeEffectArgs.effects->size(), 1);

    kivsee_render::Effect *effect = *decodeEffectArgs.effects->begin();
    effect->Render(0);

    // check that the value is written to the leds array
    assertRenderedPixel(&leds[1]);

    // check that the other pixels in the array where not affected
    ASSERT_EQ(leds[0].val, 0.0);
    ASSERT_EQ(leds[2].val, 0.0);
}

TEST(EffectSegments, SegmentNotFoundInStore)
{
    pb_istream_t effect_stream = createPbStreamSingleEffect("seg");

    // segment store for test
    kivsee_render::HSV leds[3];
    kivsee_render::segments::SegmentsMap segmentsMap;

    // decode args
    kivsee_render::DecodeEffectArgs decodeEffectArgs;
    decodeEffectArgs.segmentsMap = &segmentsMap;
    decodeEffectArgs.effects = new std::list<kivsee_render::Effect *>();
    void *arg = &decodeEffectArgs;

    bool decodeSuccess = ::kivsee_render::DecodeEffectFromPbStream(&effect_stream, nullptr, &arg);
    ASSERT_FALSE(decodeSuccess);
}

TEST(EffectSegments, EmptySegmentInProtoFetchAll)
{
    pb_istream_t effect_stream = createPbStreamSingleEffect("");

    // segment store for test
    kivsee_render::HSV leds[3];
    kivsee_render::segments::SegmentsMap segmentsMap;
    kivsee_render::segments::Segment segment;
    strcpy(segment.first, "all");
    segment.second.push_back({&leds[0], 0.0});
    segment.second.push_back({&leds[1], 0.5});
    segment.second.push_back({&leds[2], 1.0});
    segmentsMap.segments.push_back(segment);

    // decode args
    kivsee_render::DecodeEffectArgs decodeEffectArgs;
    decodeEffectArgs.segmentsMap = &segmentsMap;
    decodeEffectArgs.effects = new std::list<kivsee_render::Effect *>();
    void *arg = &decodeEffectArgs;

    bool decodeSuccess = ::kivsee_render::DecodeEffectFromPbStream(&effect_stream, nullptr, &arg);
    ASSERT_TRUE(decodeSuccess);
    ASSERT_EQ(decodeEffectArgs.effects->size(), 1);

    kivsee_render::Effect *effect = *decodeEffectArgs.effects->begin();
    effect->Render(0);

    // check that the value is written to the leds array
    for (int i = 0; i < 3; i++)
    {
        assertRenderedPixel(&leds[i]);
    }
}

TEST(EffectSegments, SegmentNameTooLong)
{
    const char *segmentName = "1234567890123";
    pb_istream_t effect_stream = createPbStreamSingleEffect(segmentName);

    // segment store for test
    kivsee_render::HSV leds[3];
    kivsee_render::segments::SegmentsMap segmentsMap;
    kivsee_render::segments::Segment segment;
    strcpy(segment.first, segmentName);
    segment.second.push_back({&leds[1], 0.0});
    segmentsMap.segments.push_back(segment);

    // decode args
    kivsee_render::DecodeEffectArgs decodeEffectArgs;
    decodeEffectArgs.segmentsMap = &segmentsMap;
    decodeEffectArgs.effects = new std::list<kivsee_render::Effect *>();
    void *arg = &decodeEffectArgs;

    bool decodeSuccess = ::kivsee_render::DecodeEffectFromPbStream(&effect_stream, nullptr, &arg);
    ASSERT_FALSE(decodeSuccess);
}