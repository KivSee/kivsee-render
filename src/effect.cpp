#include <effect.h>

#include <kivsee/proto/render/v1/effects.pb.h>
#include <cmath>
#include <list>

#include <color/rainbow.h>
#include <color/const_color.h>
#include <effect/brightness.h>
#include <effect/hue.h>
#include <effect/saturation.h>
#include <effect/snake.h>

#include <segments/segments_map.h>

namespace kivsee_render
{

    bool Effect::Render(unsigned long curr_time)
    {
        if (curr_time < this->start_time || curr_time >= this->end_time)
            return false;

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
                return false;

            relTime = (relTimeInCycle - this->repeat_start) / (this->repeat_end - this->repeat_start);
        }
        Render(relTime, currCycleIndex);
        return true;
    }

    void Effect::Init(const ::kivsee_render::segments::SegmentPixels *segment_pixels, void *&effect_config)
    {
        kivsee_proto_render_v1_EffectConfig *local_effect_config = static_cast<kivsee_proto_render_v1_EffectConfig *>(effect_config);
        this->segment_pixels = segment_pixels;
        this->start_time = local_effect_config->start_time;
        this->end_time = local_effect_config->end_time;
        this->repeat_num = local_effect_config->repeat_num;
        this->repeat_start = local_effect_config->repeat_start;
        this->repeat_end = local_effect_config->repeat_end;
    }

    bool DecodeEffectFromPbStream(pb_istream_t *stream, const pb_field_t *field, void **arg)
    {
        kivsee_render::DecodeEffectArgs *effectArgs = (kivsee_render::DecodeEffectArgs *)(*arg);
        kivsee_proto_render_v1_EffectProto kivsee_proto_render_v1_EffectProto = kivsee_proto_render_v1_EffectProto_init_zero;
        void *effect_pv = NULL;

        Effect *newEffect = nullptr;

        kivsee_proto_render_v1_EffectProto.const_color.funcs.decode = &::kivsee_render::color::ConstColor::InitFromPb;
        kivsee_proto_render_v1_EffectProto.const_color.arg = &newEffect;
        kivsee_proto_render_v1_EffectProto.rainbow.funcs.decode = &::kivsee_render::color::Rainbow::InitFromPb;
        kivsee_proto_render_v1_EffectProto.rainbow.arg = &newEffect;
        kivsee_proto_render_v1_EffectProto.brightness.funcs.decode = &::kivsee_render::effect::Brightness::InitFromPb;
        kivsee_proto_render_v1_EffectProto.brightness.arg = &newEffect;
        kivsee_proto_render_v1_EffectProto.hue.funcs.decode = &::kivsee_render::effect::Hue::InitFromPb;
        kivsee_proto_render_v1_EffectProto.hue.arg = &newEffect;
        kivsee_proto_render_v1_EffectProto.saturation.funcs.decode = &::kivsee_render::effect::Saturation::InitFromPb;
        kivsee_proto_render_v1_EffectProto.saturation.arg = &newEffect;
        kivsee_proto_render_v1_EffectProto.snake.funcs.decode = &::kivsee_render::effect::Snake::InitFromPb;
        kivsee_proto_render_v1_EffectProto.snake.arg = &newEffect;
        
        bool success = pb_decode(stream, kivsee_proto_render_v1_EffectProto_fields, &kivsee_proto_render_v1_EffectProto);
        if (!success)
            return false;

        const char *segment = kivsee_proto_render_v1_EffectProto.effect_config.segments;
        const char *segmentOrAll = segment[0] == '\0' ? "all" : segment;
        ::kivsee_render::segments::SegmentPixels *segmentPixels = effectArgs->segmentsMap->getPixelsForSegment(segmentOrAll);
        if (!segmentPixels)
        {
            stream->errmsg = "segment name not found in store";
            delete newEffect;
            return false;
        }
        effect_pv = (void *)(&(kivsee_proto_render_v1_EffectProto.effect_config));
        newEffect->Init(segmentPixels, effect_pv);
        effectArgs->effects->push_back(newEffect);
        return true;
    }

} // namespace kivsee_render