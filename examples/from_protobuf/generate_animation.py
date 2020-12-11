# import functions_pb2
import sys
sys.path.append('../../proto')
import effects_pb2

animation = effects_pb2.AnimationProto()
effect = animation.effects.add()

effect.effect_config.start_time = 1000
effect.effect_config.end_time = 5000
effect.rainbow.hue_start.linear.start = 0.0
effect.rainbow.hue_start.linear.end = 1.0
effect.rainbow.hue_end.linear.start = 1.0
effect.rainbow.hue_end.linear.end = 2.0

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

msg = animation.SerializeToString();
encoded_bytes = ", ".join(str(c) for c in msg)

f = open("msg.h", "w")
f.write('#include "Arduino.h"\n')
f.write('uint8_t msg[] = {' + encoded_bytes + '};\n')
f.close()

print()