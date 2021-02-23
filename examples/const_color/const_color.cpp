#include "Arduino.h"
#include <NeoPixelBus.h>

#include <pb_encode.h>
#include <pb_decode.h>

#define DATA_PIN 0
#define NUM_LEDS 25

#include <color/const_color.h>
#include <effect.h>
#include <hsv.h>
// ConstColorEffectConfig config {true, {0.5, 1.0, 1.0}};
// kivsee_render::color::ConstColor *effect = new kivsee_render::color::ConstColor(config);

kivsee_render::Effect *effect;
kivsee_render::HSV leds[NUM_LEDS];
std::vector<kivsee_render::HSV *> segment(NUM_LEDS);
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> leds_rgb(NUM_LEDS, DATA_PIN);

void setup()
{
    Serial.begin(115200);

    RainbowEffectConfig config;
    // config.hue_start.funcs.encode = &EncodeFloatFunction;
    // config.has_hue_start = true;
    // config.hue_start.which_function = FloatFunction_linear_tag;
    // config.hue_start.function.linear = LinearFloatFunctionConfig{0.0, 1.0};
    // config.has_hue_end = true;
    // config.hue_end.which_function = FloatFunction_linear_tag;
    // config.hue_end.function.linear = LinearFloatFunctionConfig{2.0, 0.0};

    uint8_t buffer[100] = {10, 33, 10, 6, 8, 232, 7, 16, 136, 39, 26, 23, 10, 7, 18, 5, 21, 0, 0, 128, 63, 18, 12, 18, 10, 13, 0, 0, 128, 63, 21, 0, 0, 0, 64};
    // pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    // pb_encode(&stream, RainbowEffectConfig_fields, &config);
    // printf("Encoded size is %d\n", stream.bytes_written);

    pb_istream_t in_stream = pb_istream_from_buffer(buffer, sizeof(buffer));
    AnimationProto animation;
    animation.effects.funcs.decode = &kivsee_render::DecodeEffectFromPbStream;
    animation.effects.arg = &effect;
    pb_decode(&in_stream, AnimationProto_fields, &animation);
    
    leds_rgb.Begin();
    for (int i = 0; i < NUM_LEDS; i++)
    {
        segment[i] = &leds[i];
    }
    effect->Init(&segment);
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

    effect->Render(time % 10000);
    for (int i = 0; i < NUM_LEDS; i++)
    {
        const kivsee_render::HSV &hsvVal = leds[i];
        float normalizedBrightness = hsvVal.val * hsvVal.val;
        HsbColor neoPixelColor(fmod(hsvVal.hue, 1.0f), hsvVal.sat, normalizedBrightness);

        leds_rgb.SetPixelColor(i, neoPixelColor);
    }
    leds_rgb.Show();
}
