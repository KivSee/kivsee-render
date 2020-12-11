#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <vector>
#include <hsv.h>
#include <pb_decode.h>
#include <effects.pb.h>


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

        void Init(const std::vector<HSV *> *pixels)
        {
            this->pixels = pixels;
        }

        void InitTimingFromPb(const EffectConfig &effect_config) {
            this->start_time = effect_config.start_time;
            this->end_time = effect_config.end_time;
            this->repeat_num = effect_config.repeat_num;
            this->repeat_start = effect_config.repeat_start;
            this->repeat_end = effect_config.repeat_end;
        }

    protected:
        unsigned long start_time, end_time;
        float repeat_num, repeat_start, repeat_end;
        const std::vector<HSV *> *pixels;

        int lastCycleIndex = -1;
    };

    bool DecodeEffectFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg);

} // namespace kivsee_render

#endif // __EFFECT_H__
