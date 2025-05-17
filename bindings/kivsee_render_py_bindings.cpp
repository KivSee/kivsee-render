#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "led_controller.h"

namespace py = pybind11;

PYBIND11_MODULE(kivsee_render, m) {
    m.doc() = "Python bindings for kivsee-render";

    // Bind the HSV struct
    py::class_<kivsee_render::HSV>(m, "HSV")
        .def(py::init<>())
        .def(py::init<float, float, float>())
        .def_readwrite("hue", &kivsee_render::HSV::hue)
        .def_readwrite("sat", &kivsee_render::HSV::sat)
        .def_readwrite("val", &kivsee_render::HSV::val);

    // Bind the LedController class
    py::class_<kivsee_render::LedController>(m, "LedController")
        .def(py::init<size_t>())
        .def("init_from_proto_buffers", [](kivsee_render::LedController& self, py::bytes animation_buffer, py::bytes segments_map_buffer) {
            py::buffer_info animation_info(py::buffer(animation_buffer).request());
            py::buffer_info segments_info(py::buffer(segments_map_buffer).request());
            
            return self.InitFromProtoBuffers(
                static_cast<const uint8_t*>(animation_info.ptr),
                animation_info.size,
                static_cast<const uint8_t*>(segments_info.ptr),
                segments_info.size
            );
        })
        .def("render", [](kivsee_render::LedController& self, unsigned int time_ms) {
            const kivsee_render::HSV* leds = self.Render(time_ms);
            size_t num_leds = self.GetNumLeds();
            
            // Create a numpy array of shape (num_leds, 3) for HSV values
            std::vector<size_t> shape = {num_leds, 3};
            auto result = py::array_t<float>(shape);
            py::buffer_info buf = result.request();
            float* ptr = static_cast<float*>(buf.ptr);
            
            // Copy the data
            for (size_t i = 0; i < num_leds; i++) {
                ptr[i * 3] = leds[i].hue;     // hue
                ptr[i * 3 + 1] = leds[i].sat; // sat
                ptr[i * 3 + 2] = leds[i].val; // val
            }
            
            return result;
        })
        .def("get_num_leds", &kivsee_render::LedController::GetNumLeds);
}
