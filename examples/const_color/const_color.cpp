#include "Arduino.h"
#include <NeoPixelBus.h>

#include <pb_encode.h>
#include <pb_decode.h>

#define DATA_PIN 2
#define NUM_LEDS 25

#include <color/const_color.h>
#include <color/rainbow.h>
#include <hsv.h>
// ConstColorEffectConfig config {true, {0.5, 1.0, 1.0}};
// kivsee_render::color::ConstColor *effect = new kivsee_render::color::ConstColor(config);

kivsee_render::color::Rainbow *effect;
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

    uint8_t buffer[100] = {10, 35, 58, 33, 10, 7, 18, 5, 21, 0, 0, 128, 63, 21, 0, 0, 128, 63, 26, 12, 34, 10, 13, 0, 0, 160, 64, 21, 0, 0, 128, 62, 37, 0, 0, 128, 63, 18, 7, 10, 5, 13, 0, 0, 128, 63
};
    // pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    // pb_encode(&stream, RainbowEffectConfig_fields, &config);
    // printf("Encoded size is %d\n", stream.bytes_written);

    pb_istream_t in_stream = pb_istream_from_buffer(buffer, sizeof(buffer));

    effect = new kivsee_render::color::Rainbow();
    effect->InitFromPb(&in_stream);

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
    effect->Render((time % 10000) / 10000.0, 0);
    for (int i = 0; i < NUM_LEDS; i++)
    {
        const kivsee_render::HSV &hsvVal = leds[i];
        float normalizedBrightness = hsvVal.val * hsvVal.val;
        HsbColor neoPixelColor(fmod(hsvVal.hue, 1.0f), hsvVal.sat, normalizedBrightness);

        leds_rgb.SetPixelColor(i, neoPixelColor);
    }
    leds_rgb.Show();
}
