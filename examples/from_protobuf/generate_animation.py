# import functions_pb2
import sys
sys.path.append('../../proto')
import effects_pb2

animation = effects_pb2.AnimationProto()
animation.duration_ms = 5000
animation.num_repeats = 100

# effect = animation.effects.add()
# effect.effect_config.start_time = 0
# effect.effect_config.end_time = 1000
# effect.rainbow.hue_start.linear.start = 0.0
# effect.rainbow.hue_start.linear.end = 1.0
# effect.rainbow.hue_end.linear.start = 1.0
# effect.rainbow.hue_end.linear.end = 2.0

# effect = animation.effects.add()
# effect.effect_config.start_time = 1000
# effect.effect_config.end_time = 2000
# effect.rainbow.hue_start.const_value.value = 0.0
# effect.rainbow.hue_end.const_value.value = 1.0

effect = animation.effects.add()
effect.effect_config.start_time = 0
effect.effect_config.end_time = 4000
effect.const_color.color.hue = 0.5
effect.const_color.color.sat = 0.8
effect.const_color.color.val = 1.0

# effect = animation.effects.add()
# effect.effect_config.start_time = 0
# effect.effect_config.end_time = 4000
# effect.brightness.mult_factor.sin.min = 0.5
# effect.brightness.mult_factor.sin.max = 1
# effect.brightness.mult_factor.sin.phase = -0.25
# effect.brightness.mult_factor.sin.repeats = 3

effect = animation.effects.add()
effect.effect_config.start_time = 0
effect.effect_config.end_time = 4000
effect.saturation.mult_factor.sin.min = 0.5
effect.saturation.mult_factor.sin.max = 1
effect.saturation.mult_factor.sin.phase = -0.25
effect.saturation.mult_factor.sin.repeats = 3


# effect = animation.effects.add()
# effect.effect_config.start_time = 0
# effect.effect_config.end_time = 4000
# effect.hue.offset_factor.steps.num_steps = 4
# effect.hue.offset_factor.steps.diff_per_step = 0.25
# effect.hue.offset_factor.steps.first_step_value = 0.0

# config = effects_pb2.RainbowEffectConfig()
# config.hue_start.const_value.value = 0.0
# config.hue_end.const_value.value = 1.0

# config.hue_start.linear.start = 0.0
# config.hue_start.linear.end = 1.0
# config.hue_end.const_value.value = 1.0

# config.hue_start.comb2.f1.linear.start = 0.0
# config.hue_start.comb2.f1.linear.end = 1.0
# config.hue_start.comb2.amount1 = 1.0
# config.hue_start.comb2.f2.steps.num_steps = 5
# config.hue_start.comb2.f2.steps.diff_per_step = 0.25
# config.hue_start.comb2.amount2 = 1.0
# config.hue_end.const_value.value = 1.0

print(animation)
msg = animation.SerializeToString();
encoded_bytes = ", ".join(str(c) for c in msg)

f = open("msg.h", "w")
f.write('#include "Arduino.h"\n')
f.write('uint8_t msg[] = {' + encoded_bytes + '};\n')
f.close()

print()