#include <effect.h>
#include <cmath>

namespace kivsee_render
{

    void Effect::Render(unsigned long curr_time)
    {

        float relTime = ((float)(curr_time - start_time) / (float)(end_time - start_time));
        int currCycleIndex = 0;
        if (this->repeatNum > 0.0f)
        { // has repeats - change relTime and calculate cycle index

            float cycleTime = relTime * this->repeatNum;
            float relTimeInCycle = fmod(cycleTime, 1.0f);
            currCycleIndex = floor(cycleTime);

            if (currCycleIndex != this->lastCycleIndex)
            {
                this->lastCycleIndex = currCycleIndex;
                NewCycle(currCycleIndex);
            }

            // check if a "repeat" function should be rendered for this time
            if (relTimeInCycle < this->repeatStart || relTimeInCycle > this->repeatEnd)
                return;

            relTime = (relTimeInCycle - this->repeatStart) / (this->repeatEnd - this->repeatStart);
        }
        Render(relTime, currCycleIndex);
    }

} // namespace kivsee_render