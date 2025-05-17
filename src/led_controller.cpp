#include "led_controller.h"

namespace kivsee_render {

LedController::LedController(size_t num_leds)
    : num_leds_(num_leds)
    , leds_(new HSV[num_leds])
    , segment_(num_leds)
    , animation_(nullptr)
    , segments_map_(nullptr) {
    // Initialize the segment vector with pointers to the LED array
    for (size_t i = 0; i < num_leds; i++) {
        segment_[i] = &leds_[i];
    }
}

LedController::~LedController() {
    delete[] leds_;
    delete animation_;
    delete segments_map_;
}

bool LedController::InitFromProtoBuffers(const uint8_t* animation_buffer, size_t animation_size,
                                       const uint8_t* segments_map_buffer, size_t segments_map_size) {
    // Clean up any existing objects
    delete animation_;
    delete segments_map_;
    animation_ = nullptr;
    segments_map_ = nullptr;

    // Create protobuf input streams
    pb_istream_t animation_stream = pb_istream_from_buffer(animation_buffer, animation_size);
    pb_istream_t segments_map_stream = pb_istream_from_buffer(segments_map_buffer, segments_map_size);

    // Decode segments map
    segments::SegmentsMapDecodeArgs segments_map_decode_args;
    segments_map_decode_args.out_segments_map = &segments_map_;
    segments_map_decode_args.leds_array = leds_;
    void* arg = &segments_map_decode_args;
    if (!segments::DecodeSegmentsMapFromPbStream(&segments_map_stream, nullptr, &arg)) {
        return false;
    }

    // Decode animation
    kivsee_render::DecodeAnimationArgs args = { segments_map_ };
    void* arg_animation = &args;
    if (!DecodeAnimationFromPbStream(&animation_stream, nullptr, &arg_animation)) {
        return false;
    }

    // Store the animation in the class
    animation_ = (::kivsee_render::Animation *)arg_animation;

    return true;
}

const HSV* LedController::Render(unsigned int time_ms) {
    // Clear all LEDs
    for (size_t i = 0; i < num_leds_; i++) {
        HSV& hsvVal = leds_[i];
        hsvVal.hue = 0.0f;
        hsvVal.sat = 0.0f;
        hsvVal.val = 0.0f;
    }

    // Render the animation
    if (animation_) {
        animation_->Render(time_ms);
    }

    return leds_;
}

} // namespace kivsee_render 