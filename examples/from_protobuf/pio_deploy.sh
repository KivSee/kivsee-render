rm msg.h
rm segments_map_config.h

python3 generate_animation.py
python3 generate_segments.py

pio ci --board=esp32dev --lib "../../" --project-option="lib_deps=nanopb, NeoPixelBus" --project-option="targets=upload" from_protobuf.cpp msg.h segments_map_config.h
#pio ci --board=esp32dev --lib "../../" --project-option="lib_deps=nanopb, NeoPixelBus" --project-option="targets=upload" --project-option="upload_port=/dev/cu.SLAB_USBtoUART" from_protobuf.cpp msg.h
#pio ci --board=esp32doit-devkit-v1 --lib "../../" --project-option="lib_deps=nanopb, NeoPixelBus" --project-option="targets=upload" from_protobuf.cpp msg.h