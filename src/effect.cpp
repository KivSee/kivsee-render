#include <effect.h>

#include <effects.pb.h>
#include <cmath>

#include <color/rainbow.h>

namespace kivsee_render
{

    void Effect::Render(unsigned long curr_time)
    {
        if (curr_time < this->start_time || curr_time >= this->end_time)
            return;

        float relTime = ((float)(curr_time - start_time) / (float)(end_time - start_time));
        int currCycleIndex = -1;
        if (this->repeat_num > 0.0f)
        { // has repeats - change relTime and calculate cycle index

            float cycleTime = relTime * this->repeat_num;
            float relTimeInCycle = fmod(cycleTime, 1.0f);
            currCycleIndex = floor(cycleTime);

            if (currCycleIndex != this->lastCycleIndex)
            {
                this->lastCycleIndex = currCycleIndex;
                NewCycle(currCycleIndex);
            }

            // check if a "repeat" function should be rendered for this time
            if (relTimeInCycle < this->repeat_start || relTimeInCycle > this->repeat_end)
                return;

            relTime = (relTimeInCycle - this->repeat_start) / (this->repeat_end - this->repeat_start);
        }
        Render(relTime, currCycleIndex);
    }

    bool DecodeEffectFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg)
    {
        EffectProto effectProto = EffectProto_init_zero;

        Effect *newEffect = nullptr;

        effectProto.rainbow.funcs.decode = &::kivsee_render::color::Rainbow::InitFromPb;
        effectProto.rainbow.arg = &newEffect;

        pb_decode(stream, EffectProto_fields, &effectProto);

        newEffect->InitTimingFromPb(effectProto.effect_config);
        *((Effect **)*arg) = newEffect;

        return true;
    }

} // namespace kivsee_render