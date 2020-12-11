#include "msg.h"

#include "Arduino.h"
#include <NeoPixelBus.h>

#include <pb_decode.h>

#define DATA_PIN 2
#define NUM_LEDS 25

#include <effect.h>
#include <hsv.h>

kivsee_render::Effect *effect;
kivsee_render::HSV leds[NUM_LEDS];
std::vector<kivsee_render::HSV *> segment(NUM_LEDS);
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> leds_rgb(NUM_LEDS, DATA_PIN);

void setup()
{
    Serial.begin(115200);

    pb_istream_t in_stream = pb_istream_from_buffer(msg, sizeof(msg));
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
