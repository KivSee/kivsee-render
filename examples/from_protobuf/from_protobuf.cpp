#include "msg.h"
#include "segments_map_config.h"

#include "Arduino.h"
#include <NeoPixelBus.h>

#include <pb_decode.h>

#define DATA_PIN 2
#define NUM_LEDS 25

#include <effect.h>
#include <animation.h>
#include <segments/segments_map.h>
#include <hsv.h>

kivsee_render::Animation *animation;
kivsee_render::segments::SegmentsMap *segments_map;
kivsee_render::HSV leds[NUM_LEDS];
std::vector<kivsee_render::HSV *> segment(NUM_LEDS);
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> leds_rgb(NUM_LEDS, DATA_PIN);

void setup()
{
    Serial.begin(115200);
    Serial.println("started");

    pb_istream_t animation_stream = pb_istream_from_buffer(msg, sizeof(msg));
    void *arg_animation = &animation;
    ::kivsee_render::DecodeAnimationFromPbStream(&animation_stream, nullptr, &arg_animation);

    pb_istream_t segments_map_stream = pb_istream_from_buffer(segments_map_config, sizeof(segments_map_config));
    ::kivsee_render::segments::SegmentsMapDecodeArgs segments_map_decode_args;
    segments_map_decode_args.out_segments_map = &segments_map;
    segments_map_decode_args.leds_array = leds;
    void *arg = &segments_map_decode_args;
    ::kivsee_render::segments::DecodeSegmentsMapFromPbStream(&segments_map_stream, nullptr, &arg);
    Serial.println(segments_map->guid);

    leds_rgb.Begin();
    for (int i = 0; i < NUM_LEDS; i++)
    {
        segment[i] = &leds[i];
    }
    for(::kivsee_render::Animation::EffectsVec::iterator it = animation->effects.begin(); it != animation->effects.end(); ++it) {
        ::kivsee_render::Effect *effect = *it;
        effect->Init(&segment);
    }
    Serial.println("finished initialization");
}

void loop()
{
    unsigned int time = millis();
    for (int i = 0; i < NUM_LEDS; i++)
    {
        kivsee_render::HSV &hsvVal = leds[i];
        hsvVal.hue = 0.0;
        hsvVal.sat = 0.0;
        hsvVal.val = 0.0;
    }

    animation->Render(time);
    for (int i = 0; i < NUM_LEDS; i++)
    {
        const kivsee_render::HSV &hsvVal = leds[i];
        float normalizedBrightness = hsvVal.val * hsvVal.val;
        HsbColor neoPixelColor(fmod(hsvVal.hue, 1.0f), hsvVal.sat, normalizedBrightness);

        leds_rgb.SetPixelColor(i, neoPixelColor);
    }
    leds_rgb.Show();
}
