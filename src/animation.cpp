
#include "animation.h"

#include <list>

namespace kivsee_render {

    ~Animation::Animation() {
        for(EffectsVec::iterator it = effects.begin(); it != effects.end(); ++it) {
            Effect *effect = *it;
            delete effect;
        }
    }

    bool Animation::Render(unsigned long curr_time) {
        int iteration = curr_time / duration_ms;
        int time_in_iteration = curr_time % duration_ms;
        if(num_repeats > 0 && iteration >= num_repeats) return false;

        for(EffectsVec::iterator it = effects.begin(); it != effects.end(); ++it) {
            Effect *effect = *it;
            effect->Render(time_in_iteration);
        }
        return true;
    }

    bool DecodeAnimationFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg) {

        std::list<Effect *> effects;

        AnimationProto animation = AnimationProto_init_zero;
        animation.effects.funcs.decode = &kivsee_render::DecodeEffectFromPbStream;
        animation.effects.arg = &effects;

        bool success = pb_decode(stream, AnimationProto_fields, &animation);
        if(!success) return false;

        if(animation.duration_ms == 0) return false;

        Animation *newAnimation = new Animation(effects.begin(), effects.end(), animation.duration_ms, animation.num_repeats);
        *((Animation **) *arg) = newAnimation;
        return true;
    }



}