
#include "animation.h"
#include <effects.pb.h>

#include <list>

namespace kivsee_render
{

    Animation::~Animation()
    {
        for (EffectsVec::iterator it = effects.begin(); it != effects.end(); ++it)
        {
            Effect *effect = *it;
            delete effect;
        }
    }

    RenderStats Animation::Render(unsigned long curr_time)
    {
        int iteration = curr_time / duration_ms;
        int time_in_iteration = curr_time % duration_ms;
        if (num_repeats > 0 && iteration >= num_repeats)
        {
            return {
                .is_rendering = false,
                .num_effects_rendered = 0};
        }

        uint32_t num_effects_rendered = 0;
        for (EffectsVec::iterator it = effects.begin(); it != effects.end(); ++it)
        {
            Effect *effect = *it;
            bool rendered = effect->Render(time_in_iteration);
            if (rendered)
            {
                num_effects_rendered++;
            }
        }
        
        return {
            .is_rendering = true,
            .num_effects_rendered = num_effects_rendered};
    }

    bool DecodeAnimationFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg)
    {

        kivsee_render::segments::SegmentsMap *segmentsMap = ((DecodeAnimationArgs *)(*arg))->segmentsMap;

        std::list<Effect *> effects;

        AnimationProto animation = AnimationProto_init_zero;
        animation.effects.funcs.decode = &kivsee_render::DecodeEffectFromPbStream;
        kivsee_render::DecodeEffectArgs args = {
            segmentsMap,
            &effects};
        animation.effects.arg = &args;

        bool success = pb_decode(stream, AnimationProto_fields, &animation);
        if (!success)
            return false;

        if (animation.duration_ms == 0)
            return false;

        Animation *newAnimation = new Animation(effects.begin(), effects.end(), animation.duration_ms, animation.num_repeats);
        *arg = (void *)newAnimation;
        return true;
    }

}