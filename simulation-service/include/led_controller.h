#ifndef __LED_CONTROLLER_H__
#define __LED_CONTROLLER_H__

#include <hsv.h>
#include <animation.h>
#include <segments/segments_map.h>
#include "pb_decode.h"

namespace kivsee_simulation {

class LedController {
public:
    LedController(size_t num_leds);
    ~LedController();

    // Initialize from protobuf buffers
    bool InitFromProtoBuffers(const uint8_t* animation_buffer, size_t animation_size,
                            const uint8_t* segments_map_buffer, size_t segments_map_size);

    // Render at the given time and get the LED buffer
    const kivsee_render::HSV* Render(unsigned int time_ms);

    // Get the number of LEDs
    size_t GetNumLeds() const { return num_leds_; }

private:
    const size_t num_leds_;
    kivsee_render::HSV* leds_;
    std::vector<kivsee_render::HSV*> segment_;
    kivsee_render::Animation* animation_;
    kivsee_render::segments::SegmentsMap* segments_map_;
};

} // namespace kivsee_simulation

#endif // __LED_CONTROLLER_H__ 