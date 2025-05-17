#ifndef __LED_CONTROLLER_H__
#define __LED_CONTROLLER_H__

#include <hsv.h>
#include <animation.h>
#include <segments/segments_map.h>
#include "pb_decode.h"

namespace kivsee_render {

class LedController {
public:
    LedController(size_t num_leds);
    ~LedController();

    // Initialize from protobuf buffers
    bool InitFromProtoBuffers(const uint8_t* animation_buffer, size_t animation_size,
                            const uint8_t* segments_map_buffer, size_t segments_map_size);

    // Render at the given time and get the LED buffer
    const HSV* Render(unsigned int time_ms);

    // Get the number of LEDs
    size_t GetNumLeds() const { return num_leds_; }

private:
    const size_t num_leds_;
    HSV* leds_;
    std::vector<HSV*> segment_;
    Animation* animation_;
    segments::SegmentsMap* segments_map_;
};

} // namespace kivsee_render

#endif // __LED_CONTROLLER_H__ 