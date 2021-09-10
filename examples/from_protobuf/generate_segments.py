import sys
sys.path.append('../../proto')
import segments_pb2

segments_map = segments_pb2.SegmentsMapConfig()
segments_map.guid = 1234
segments_map.number_of_pixels = 50

seg1 = segments_map.segments.add()
seg1.name = 'sapir'
seg1.indices.extend(range(0, 30))

seg2 = segments_map.segments.add()
seg2.name = 'bigler'
seg2.indices.extend([7, 19, 3, 41])

seg3 = segments_map.segments.add()
seg3.name = 'amir'
seg3.indices.extend([10, 11, 12, 13])

print(segments_map)
msg = segments_map.SerializeToString();
encoded_bytes = ", ".join(str(c) for c in msg)

f = open("segments_map_config.h", "w")
f.write('uint8_t segments_map_config[] = {' + encoded_bytes + '};\n')
f.close()
