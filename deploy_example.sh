# Amir's Linux
pio ci --board=esp32doit-devkit-v1 --lib "../../" --project-option="lib_deps=nanopb, NeoPixelBus" --project-option="targets=upload" const_color.cpp

pio device monitor -b 115200

# Sapir's Mac
# pio ci --board=esp32dev --lib "../../" --project-option="lib_deps=nanopb, NeoPixelBus" --project-option="upload_port=/dev/cu.SLAB_USBtoUART" --project-option="targets=upload" const_color.cpp
