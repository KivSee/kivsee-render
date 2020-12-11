#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <pb_decode.h>

#include <effect.h>
#include <vector>

namespace kivsee_render {

    class Animation {

        public:
            template<class EffectsIt>
            Animation(EffectsIt effectsFirst, EffectsIt effectsLast, uint32_t duration_ms, uint32_t num_repeats) : 
                effects(effectsFirst, effectsLast),
                duration_ms(duration_ms),
                num_repeats(num_repeats)
                 {}

            ~Animation();

            bool Render(unsigned long curr_time);

        public:
            typedef std::vector<Effect *> EffectsVec;
            EffectsVec effects;
            uint32_t duration_ms;
            uint32_t num_repeats;

    };

    bool DecodeAnimationFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg);

}

#endif // __ANIMATION_H__