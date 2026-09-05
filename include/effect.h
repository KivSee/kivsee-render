#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <vector>
#include <hsv.h>
#include "pb_decode.h"
#include "segments/segments_map.h"
#include "esp_heap_caps.h"

namespace kivsee_render
{
    class Effect
    {

    public:
        virtual ~Effect() {}

        // Effect objects are small (well under the platform's
        // CONFIG_SPIRAM_MALLOC_ALWAYSINTERNAL threshold, so the default allocator
        // would always place them in scarce internal RAM) but numerous -- a large
        // decoded animation can hold thousands of them. Force them into PSRAM
        // (8MB vs ~350KB internal) so effect count is bounded by PSRAM capacity
        // instead of internal-heap fragmentation. Falls back to the default
        // allocator if PSRAM is exhausted or unavailable.
        static void *operator new(size_t size)
        {
            void *p = heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
            return p ? p : ::operator new(size);
        }

        static void operator delete(void *p)
        {
            heap_caps_free(p);
        }

    protected:
        virtual void Render(float rel_time, int cycle_index) = 0;

        // animation can be notified via this virtual method on a new cycle that starts.
        // each derived class can choose to implement this function if it likes, or just ignore the event
        virtual void NewCycle(int cycleIndex) {}

    public:
        bool Render(unsigned long curr_time);

        void Init(const ::kivsee_render::segments::SegmentPixels *segment_pixels, void * &effect_config);

    protected:
        unsigned long start_time, end_time;
        float repeat_num, repeat_start, repeat_end;
        const ::kivsee_render::segments::SegmentPixels *segment_pixels;

        int lastCycleIndex = -1;
    };

    struct DecodeEffectArgs
    {
        kivsee_render::segments::SegmentsMap *segmentsMap;
        std::list<Effect *> *effects;
    };

    bool DecodeEffectFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg);

} // namespace kivsee_render

#endif // __EFFECT_H__
