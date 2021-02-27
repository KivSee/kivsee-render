# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: effects.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import functions_pb2 as functions__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='effects.proto',
  package='',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\reffects.proto\x1a\x0f\x66unctions.proto\",\n\x03HSV\x12\x0b\n\x03hue\x18\x01 \x01(\x02\x12\x0b\n\x03sat\x18\x02 \x01(\x02\x12\x0b\n\x03val\x18\x03 \x01(\x02\"-\n\x16\x43onstColorEffectConfig\x12\x13\n\x05\x63olor\x18\x01 \x01(\x0b\x32\x04.HSV\"Y\n\x13RainbowEffectConfig\x12!\n\thue_start\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\x12\x1f\n\x07hue_end\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\"=\n\x16\x42rightnessEffectConfig\x12#\n\x0bmult_factor\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\"8\n\x0fHueEffectConfig\x12%\n\roffset_factor\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\"6\n\x0fSatEffectConfig\x12#\n\x0bmult_factor\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\"Q\n\x13SegmentEffectConfig\x12\x1d\n\x05start\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\x12\x1b\n\x03\x65nd\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\"a\n\x13GlitterEffectConfig\x12!\n\tintensity\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\x12\'\n\x0fsat_mult_factor\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\"V\n\x11SnakeEffectConfig\x12\x1c\n\x04head\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\x12#\n\x0btail_length\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\"\x9e\x01\n\x15\x41lternateEffectConfig\x12\x16\n\x0enumberOfPixels\x18\x01 \x01(\r\x12\"\n\nhue_offset\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\x12 \n\x08sat_mult\x18\x03 \x01(\x0b\x32\x0e.FloatFunction\x12\'\n\x0f\x62rightness_mult\x18\x04 \x01(\x0b\x32\x0e.FloatFunction\"\x84\x01\n\x0c\x45\x66\x66\x65\x63tConfig\x12\x12\n\nstart_time\x18\x01 \x01(\r\x12\x10\n\x08\x65nd_time\x18\x02 \x01(\r\x12\x10\n\x08segments\x18\x03 \x01(\t\x12\x12\n\nrepeat_num\x18\x04 \x01(\x02\x12\x14\n\x0crepeat_start\x18\x05 \x01(\x02\x12\x12\n\nrepeat_end\x18\x06 \x01(\x02\"\x8e\x02\n\x0b\x45\x66\x66\x65\x63tProto\x12$\n\reffect_config\x18\x01 \x01(\x0b\x32\r.EffectConfig\x12.\n\x0b\x63onst_color\x18\x02 \x01(\x0b\x32\x17.ConstColorEffectConfigH\x00\x12\'\n\x07rainbow\x18\x03 \x01(\x0b\x32\x14.RainbowEffectConfigH\x00\x12-\n\nbrightness\x18\x04 \x01(\x0b\x32\x17.BrightnessEffectConfigH\x00\x12\x1f\n\x03hue\x18\x05 \x01(\x0b\x32\x10.HueEffectConfigH\x00\x12&\n\nsaturation\x18\x06 \x01(\x0b\x32\x10.SatEffectConfigH\x00\x42\x08\n\x06\x65\x66\x66\x65\x63t\"Y\n\x0e\x41nimationProto\x12\x1d\n\x07\x65\x66\x66\x65\x63ts\x18\x01 \x03(\x0b\x32\x0c.EffectProto\x12\x13\n\x0b\x64uration_ms\x18\x02 \x01(\r\x12\x13\n\x0bnum_repeats\x18\x03 \x01(\rb\x06proto3'
  ,
  dependencies=[functions__pb2.DESCRIPTOR,])




_HSV = _descriptor.Descriptor(
  name='HSV',
  full_name='HSV',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='hue', full_name='HSV.hue', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='sat', full_name='HSV.sat', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='val', full_name='HSV.val', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=34,
  serialized_end=78,
)


_CONSTCOLOREFFECTCONFIG = _descriptor.Descriptor(
  name='ConstColorEffectConfig',
  full_name='ConstColorEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='color', full_name='ConstColorEffectConfig.color', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=80,
  serialized_end=125,
)


_RAINBOWEFFECTCONFIG = _descriptor.Descriptor(
  name='RainbowEffectConfig',
  full_name='RainbowEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='hue_start', full_name='RainbowEffectConfig.hue_start', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='hue_end', full_name='RainbowEffectConfig.hue_end', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=127,
  serialized_end=216,
)


_BRIGHTNESSEFFECTCONFIG = _descriptor.Descriptor(
  name='BrightnessEffectConfig',
  full_name='BrightnessEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='mult_factor', full_name='BrightnessEffectConfig.mult_factor', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=218,
  serialized_end=279,
)


_HUEEFFECTCONFIG = _descriptor.Descriptor(
  name='HueEffectConfig',
  full_name='HueEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='offset_factor', full_name='HueEffectConfig.offset_factor', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=281,
  serialized_end=337,
)


_SATEFFECTCONFIG = _descriptor.Descriptor(
  name='SatEffectConfig',
  full_name='SatEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='mult_factor', full_name='SatEffectConfig.mult_factor', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=339,
  serialized_end=393,
)


_SEGMENTEFFECTCONFIG = _descriptor.Descriptor(
  name='SegmentEffectConfig',
  full_name='SegmentEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='start', full_name='SegmentEffectConfig.start', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='end', full_name='SegmentEffectConfig.end', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=395,
  serialized_end=476,
)


_GLITTEREFFECTCONFIG = _descriptor.Descriptor(
  name='GlitterEffectConfig',
  full_name='GlitterEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='intensity', full_name='GlitterEffectConfig.intensity', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='sat_mult_factor', full_name='GlitterEffectConfig.sat_mult_factor', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=478,
  serialized_end=575,
)


_SNAKEEFFECTCONFIG = _descriptor.Descriptor(
  name='SnakeEffectConfig',
  full_name='SnakeEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='head', full_name='SnakeEffectConfig.head', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='tail_length', full_name='SnakeEffectConfig.tail_length', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=577,
  serialized_end=663,
)


_ALTERNATEEFFECTCONFIG = _descriptor.Descriptor(
  name='AlternateEffectConfig',
  full_name='AlternateEffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='numberOfPixels', full_name='AlternateEffectConfig.numberOfPixels', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='hue_offset', full_name='AlternateEffectConfig.hue_offset', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='sat_mult', full_name='AlternateEffectConfig.sat_mult', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='brightness_mult', full_name='AlternateEffectConfig.brightness_mult', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=666,
  serialized_end=824,
)


_EFFECTCONFIG = _descriptor.Descriptor(
  name='EffectConfig',
  full_name='EffectConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='start_time', full_name='EffectConfig.start_time', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='end_time', full_name='EffectConfig.end_time', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='segments', full_name='EffectConfig.segments', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='repeat_num', full_name='EffectConfig.repeat_num', index=3,
      number=4, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='repeat_start', full_name='EffectConfig.repeat_start', index=4,
      number=5, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='repeat_end', full_name='EffectConfig.repeat_end', index=5,
      number=6, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=827,
  serialized_end=959,
)


_EFFECTPROTO = _descriptor.Descriptor(
  name='EffectProto',
  full_name='EffectProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='effect_config', full_name='EffectProto.effect_config', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='const_color', full_name='EffectProto.const_color', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='rainbow', full_name='EffectProto.rainbow', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='brightness', full_name='EffectProto.brightness', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='hue', full_name='EffectProto.hue', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='saturation', full_name='EffectProto.saturation', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='effect', full_name='EffectProto.effect',
      index=0, containing_type=None,
      create_key=_descriptor._internal_create_key,
    fields=[]),
  ],
  serialized_start=962,
  serialized_end=1232,
)


_ANIMATIONPROTO = _descriptor.Descriptor(
  name='AnimationProto',
  full_name='AnimationProto',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='effects', full_name='AnimationProto.effects', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='duration_ms', full_name='AnimationProto.duration_ms', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='num_repeats', full_name='AnimationProto.num_repeats', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1234,
  serialized_end=1323,
)

_CONSTCOLOREFFECTCONFIG.fields_by_name['color'].message_type = _HSV
_RAINBOWEFFECTCONFIG.fields_by_name['hue_start'].message_type = functions__pb2._FLOATFUNCTION
_RAINBOWEFFECTCONFIG.fields_by_name['hue_end'].message_type = functions__pb2._FLOATFUNCTION
_BRIGHTNESSEFFECTCONFIG.fields_by_name['mult_factor'].message_type = functions__pb2._FLOATFUNCTION
_HUEEFFECTCONFIG.fields_by_name['offset_factor'].message_type = functions__pb2._FLOATFUNCTION
_SATEFFECTCONFIG.fields_by_name['mult_factor'].message_type = functions__pb2._FLOATFUNCTION
_SEGMENTEFFECTCONFIG.fields_by_name['start'].message_type = functions__pb2._FLOATFUNCTION
_SEGMENTEFFECTCONFIG.fields_by_name['end'].message_type = functions__pb2._FLOATFUNCTION
_GLITTEREFFECTCONFIG.fields_by_name['intensity'].message_type = functions__pb2._FLOATFUNCTION
_GLITTEREFFECTCONFIG.fields_by_name['sat_mult_factor'].message_type = functions__pb2._FLOATFUNCTION
_SNAKEEFFECTCONFIG.fields_by_name['head'].message_type = functions__pb2._FLOATFUNCTION
_SNAKEEFFECTCONFIG.fields_by_name['tail_length'].message_type = functions__pb2._FLOATFUNCTION
_ALTERNATEEFFECTCONFIG.fields_by_name['hue_offset'].message_type = functions__pb2._FLOATFUNCTION
_ALTERNATEEFFECTCONFIG.fields_by_name['sat_mult'].message_type = functions__pb2._FLOATFUNCTION
_ALTERNATEEFFECTCONFIG.fields_by_name['brightness_mult'].message_type = functions__pb2._FLOATFUNCTION
_EFFECTPROTO.fields_by_name['effect_config'].message_type = _EFFECTCONFIG
_EFFECTPROTO.fields_by_name['const_color'].message_type = _CONSTCOLOREFFECTCONFIG
_EFFECTPROTO.fields_by_name['rainbow'].message_type = _RAINBOWEFFECTCONFIG
_EFFECTPROTO.fields_by_name['brightness'].message_type = _BRIGHTNESSEFFECTCONFIG
_EFFECTPROTO.fields_by_name['hue'].message_type = _HUEEFFECTCONFIG
_EFFECTPROTO.fields_by_name['saturation'].message_type = _SATEFFECTCONFIG
_EFFECTPROTO.oneofs_by_name['effect'].fields.append(
  _EFFECTPROTO.fields_by_name['const_color'])
_EFFECTPROTO.fields_by_name['const_color'].containing_oneof = _EFFECTPROTO.oneofs_by_name['effect']
_EFFECTPROTO.oneofs_by_name['effect'].fields.append(
  _EFFECTPROTO.fields_by_name['rainbow'])
_EFFECTPROTO.fields_by_name['rainbow'].containing_oneof = _EFFECTPROTO.oneofs_by_name['effect']
_EFFECTPROTO.oneofs_by_name['effect'].fields.append(
  _EFFECTPROTO.fields_by_name['brightness'])
_EFFECTPROTO.fields_by_name['brightness'].containing_oneof = _EFFECTPROTO.oneofs_by_name['effect']
_EFFECTPROTO.oneofs_by_name['effect'].fields.append(
  _EFFECTPROTO.fields_by_name['hue'])
_EFFECTPROTO.fields_by_name['hue'].containing_oneof = _EFFECTPROTO.oneofs_by_name['effect']
_EFFECTPROTO.oneofs_by_name['effect'].fields.append(
  _EFFECTPROTO.fields_by_name['saturation'])
_EFFECTPROTO.fields_by_name['saturation'].containing_oneof = _EFFECTPROTO.oneofs_by_name['effect']
_ANIMATIONPROTO.fields_by_name['effects'].message_type = _EFFECTPROTO
DESCRIPTOR.message_types_by_name['HSV'] = _HSV
DESCRIPTOR.message_types_by_name['ConstColorEffectConfig'] = _CONSTCOLOREFFECTCONFIG
DESCRIPTOR.message_types_by_name['RainbowEffectConfig'] = _RAINBOWEFFECTCONFIG
DESCRIPTOR.message_types_by_name['BrightnessEffectConfig'] = _BRIGHTNESSEFFECTCONFIG
DESCRIPTOR.message_types_by_name['HueEffectConfig'] = _HUEEFFECTCONFIG
DESCRIPTOR.message_types_by_name['SatEffectConfig'] = _SATEFFECTCONFIG
DESCRIPTOR.message_types_by_name['SegmentEffectConfig'] = _SEGMENTEFFECTCONFIG
DESCRIPTOR.message_types_by_name['GlitterEffectConfig'] = _GLITTEREFFECTCONFIG
DESCRIPTOR.message_types_by_name['SnakeEffectConfig'] = _SNAKEEFFECTCONFIG
DESCRIPTOR.message_types_by_name['AlternateEffectConfig'] = _ALTERNATEEFFECTCONFIG
DESCRIPTOR.message_types_by_name['EffectConfig'] = _EFFECTCONFIG
DESCRIPTOR.message_types_by_name['EffectProto'] = _EFFECTPROTO
DESCRIPTOR.message_types_by_name['AnimationProto'] = _ANIMATIONPROTO
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

HSV = _reflection.GeneratedProtocolMessageType('HSV', (_message.Message,), {
  'DESCRIPTOR' : _HSV,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:HSV)
  })
_sym_db.RegisterMessage(HSV)

ConstColorEffectConfig = _reflection.GeneratedProtocolMessageType('ConstColorEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _CONSTCOLOREFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:ConstColorEffectConfig)
  })
_sym_db.RegisterMessage(ConstColorEffectConfig)

RainbowEffectConfig = _reflection.GeneratedProtocolMessageType('RainbowEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _RAINBOWEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:RainbowEffectConfig)
  })
_sym_db.RegisterMessage(RainbowEffectConfig)

BrightnessEffectConfig = _reflection.GeneratedProtocolMessageType('BrightnessEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _BRIGHTNESSEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:BrightnessEffectConfig)
  })
_sym_db.RegisterMessage(BrightnessEffectConfig)

HueEffectConfig = _reflection.GeneratedProtocolMessageType('HueEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _HUEEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:HueEffectConfig)
  })
_sym_db.RegisterMessage(HueEffectConfig)

SatEffectConfig = _reflection.GeneratedProtocolMessageType('SatEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _SATEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:SatEffectConfig)
  })
_sym_db.RegisterMessage(SatEffectConfig)

SegmentEffectConfig = _reflection.GeneratedProtocolMessageType('SegmentEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _SEGMENTEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:SegmentEffectConfig)
  })
_sym_db.RegisterMessage(SegmentEffectConfig)

GlitterEffectConfig = _reflection.GeneratedProtocolMessageType('GlitterEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _GLITTEREFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:GlitterEffectConfig)
  })
_sym_db.RegisterMessage(GlitterEffectConfig)

SnakeEffectConfig = _reflection.GeneratedProtocolMessageType('SnakeEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _SNAKEEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:SnakeEffectConfig)
  })
_sym_db.RegisterMessage(SnakeEffectConfig)

AlternateEffectConfig = _reflection.GeneratedProtocolMessageType('AlternateEffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _ALTERNATEEFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:AlternateEffectConfig)
  })
_sym_db.RegisterMessage(AlternateEffectConfig)

EffectConfig = _reflection.GeneratedProtocolMessageType('EffectConfig', (_message.Message,), {
  'DESCRIPTOR' : _EFFECTCONFIG,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:EffectConfig)
  })
_sym_db.RegisterMessage(EffectConfig)

EffectProto = _reflection.GeneratedProtocolMessageType('EffectProto', (_message.Message,), {
  'DESCRIPTOR' : _EFFECTPROTO,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:EffectProto)
  })
_sym_db.RegisterMessage(EffectProto)

AnimationProto = _reflection.GeneratedProtocolMessageType('AnimationProto', (_message.Message,), {
  'DESCRIPTOR' : _ANIMATIONPROTO,
  '__module__' : 'effects_pb2'
  # @@protoc_insertion_point(class_scope:AnimationProto)
  })
_sym_db.RegisterMessage(AnimationProto)


# @@protoc_insertion_point(module_scope)
