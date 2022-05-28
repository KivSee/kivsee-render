#include "gtest/gtest.h"

#include "effects.pb.h"
#include "effect.h"
#include "hsv.h"

const int END_TIME = 30;

EffectProto testSnakeEffect(const char *segmentName) {
    EffectProto effectProto;
    effectProto.mutable_effect_config()->set_start_time(0);
    effectProto.mutable_effect_config()->set_end_time(END_TIME);
    effectProto.mutable_effect_config()->set_segments(segmentName);

    effectProto.mutable_snake()->mutable_head()->mutable_linear()->set_start(0.0);
    effectProto.mutable_snake()->mutable_head()->mutable_linear()->set_end(1.0);
    
    effectProto.mutable_snake()->mutable_tail_length()->mutable_const_value()->set_value(0.2);
    return effectProto;
}

pb_istream_t createPbStreamSnakeEffect(const char *segmentName) {
    EffectProto effectProto = testSnakeEffect(segmentName);
    size_t size = effectProto.ByteSizeLong();
    uint8_t *msgBuffer = new uint8_t[size];
    effectProto.SerializeToArray(msgBuffer, size);
    return pb_istream_from_buffer(msgBuffer, size);
}

void assertRenderedPixel(kivsee_render::HSV *pixel, float hue, float sat, float val) {
    ASSERT_FLOAT_EQ(pixel->hue, hue);
    ASSERT_FLOAT_EQ(pixel->sat, sat);
    ASSERT_FLOAT_EQ(pixel->val, val);
}

TEST(EffectSnake, BasicConfigSuccess)
{
    pb_istream_t effect_stream = createPbStreamSnakeEffect("seg");

    // segment store for test
    const kivsee_render::HSV red {0.0, 0.75, 0.5};
    kivsee_render::HSV leds[4] {red, red, red, red};
    
    kivsee_render::segments::SegmentsMap segmentsMap;
    kivsee_render::segments::Segment segment;
    strcpy(segment.first, "seg");
    segment.second.push_back({&leds[0], 0.0});
    segment.second.push_back({&leds[1], 0.25});
    segment.second.push_back({&leds[2], 0.75});
    segment.second.push_back({&leds[3], 1.0});
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
    assertRenderedPixel(&leds[0], 0.0, 0.75, 0.5);
    assertRenderedPixel(&leds[1], 0.0, 0.75, 0.0);
}


TEST(EffectSnake, BasicConfigSuccessTimeEnd)
{
    pb_istream_t effect_stream = createPbStreamSnakeEffect("seg");

    // segment store for test
    const kivsee_render::HSV red {0.0, 0.75, 0.5};
    kivsee_render::HSV leds[4] {red, red, red, red};
    
    kivsee_render::segments::SegmentsMap segmentsMap;
    kivsee_render::segments::Segment segment;
    strcpy(segment.first, "seg");
    segment.second.push_back({&leds[0], 0.0});
    segment.second.push_back({&leds[1], 0.4});
    segment.second.push_back({&leds[2], 0.5});
    segment.second.push_back({&leds[3], 1.0});
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
    effect->Render(END_TIME/2);

    // check that the value is written to the leds array
    assertRenderedPixel(&leds[0], 0.0, 0.75, 0.0);
    assertRenderedPixel(&leds[1], 0.0, 0.75, 0.25);
    assertRenderedPixel(&leds[2], 0.0, 0.75, 0.5);
    assertRenderedPixel(&leds[3], 0.0, 0.75, 0.0);

}
