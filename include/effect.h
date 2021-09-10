#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <vector>
#include <hsv.h>
#include "pb_decode.h"
#include "segments/segments_map.h"

namespace kivsee_render
{
    class Effect
    {

    public:
        virtual ~Effect() {}

    protected:
        virtual void Render(float rel_time, int cycle_index) = 0;

        // animation can be notified via this virtual method on a new cycle that starts.
        // each derived class can choose to implement this function if it likes, or just ignore the event
        virtual void NewCycle(int cycleIndex) {}

    public:
        void Render(unsigned long curr_time);

        void Init(const std::vector<HSV *> *pixels, void * &effect_config);

    protected:
        unsigned long start_time, end_time;
        float repeat_num, repeat_start, repeat_end;
        const std::vector<HSV *> *pixels;

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
