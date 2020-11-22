#ifndef __I_ANIMATIONS_H__
#define __I_ANIMATIONS_H__

#include <vector>
#include <hsv.h>

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

        void Init(const std::vector<HSV *> *pixels) {
            this->pixels = pixels;
        }
        //   void InitAnimation(const std::vector<HSV *> *pixels, const JsonObject &animationAsJsonObj) {
        //     this->pixels = pixels;
        //     this->start_time = animationAsJsonObj["s"];
        //     this->end_time = animationAsJsonObj["e"];
        //     this->repeatNum = animationAsJsonObj["rep_num"]; // will be 0.0f if missing
        //     this->repeatStart = animationAsJsonObj["rep_s"]; // will be 0.0f if missing
        //     this->repeatEnd = animationAsJsonObj["rep_e"]; // will be 0.0f if missing
        //   }

        bool IsActive(unsigned long curr_time)
        {
            return curr_time >= this->start_time && curr_time < this->end_time;
        }

    protected:
        unsigned long start_time, end_time;
        float repeatNum, repeatStart, repeatEnd;
        const std::vector<HSV *> *pixels;

        int lastCycleIndex = -1;
    };

} // namespace kivsee_render

#endif // __I_ANIMATIONS_H__
