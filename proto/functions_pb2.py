# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: functions.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='functions.proto',
  package='',
  syntax='proto3',
  serialized_pb=_b('\n\x0f\x66unctions.proto\".\n\x1d\x43onstValueFloatFunctionConfig\x12\r\n\x05value\x18\x01 \x01(\x02\"7\n\x19LinearFloatFunctionConfig\x12\r\n\x05start\x18\x01 \x01(\x02\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x02\"R\n\x16SinFloatFunctionConfig\x12\x0b\n\x03min\x18\x01 \x01(\x02\x12\x0b\n\x03max\x18\x02 \x01(\x02\x12\r\n\x05phase\x18\x03 \x01(\x02\x12\x0f\n\x07repeats\x18\x04 \x01(\x02\"^\n\x18StepsFloatFunctionConfig\x12\x11\n\tnum_steps\x18\x01 \x01(\x02\x12\x15\n\rdiff_per_step\x18\x02 \x01(\x02\x12\x18\n\x10\x66irst_step_value\x18\x03 \x01(\x02\"X\n\x19RepeatFloatFunctionConfig\x12\x15\n\rnumberOfTimes\x18\x01 \x01(\x02\x12$\n\x0c\x66uncToRepeat\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\"Q\n\x17HalfFloatFunctionConfig\x12\x1a\n\x02\x66\x31\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\x12\x1a\n\x02\x66\x32\x18\x02 \x01(\x0b\x32\x0e.FloatFunction\"t\n\x18\x43omb2FloatFunctionConfig\x12\x1a\n\x02\x66\x31\x18\x01 \x01(\x0b\x32\x0e.FloatFunction\x12\x0f\n\x07\x61mount1\x18\x02 \x01(\x02\x12\x1a\n\x02\x66\x32\x18\x03 \x01(\x0b\x32\x0e.FloatFunction\x12\x0f\n\x07\x61mount2\x18\x04 \x01(\x02\"\xd8\x02\n\rFloatFunction\x12\x35\n\x0b\x63onst_value\x18\x01 \x01(\x0b\x32\x1e.ConstValueFloatFunctionConfigH\x00\x12,\n\x06linear\x18\x02 \x01(\x0b\x32\x1a.LinearFloatFunctionConfigH\x00\x12&\n\x03sin\x18\x03 \x01(\x0b\x32\x17.SinFloatFunctionConfigH\x00\x12*\n\x05steps\x18\x04 \x01(\x0b\x32\x19.StepsFloatFunctionConfigH\x00\x12,\n\x06repeat\x18\x05 \x01(\x0b\x32\x1a.RepeatFloatFunctionConfigH\x00\x12(\n\x04half\x18\x06 \x01(\x0b\x32\x18.HalfFloatFunctionConfigH\x00\x12*\n\x05\x63omb2\x18\x07 \x01(\x0b\x32\x19.Comb2FloatFunctionConfigH\x00\x42\n\n\x08\x66unctionb\x06proto3')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CONSTVALUEFLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='ConstValueFloatFunctionConfig',
  full_name='ConstValueFloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='value', full_name='ConstValueFloatFunctionConfig.value', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=19,
  serialized_end=65,
)


_LINEARFLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='LinearFloatFunctionConfig',
  full_name='LinearFloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='start', full_name='LinearFloatFunctionConfig.start', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='end', full_name='LinearFloatFunctionConfig.end', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=67,
  serialized_end=122,
)


_SINFLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='SinFloatFunctionConfig',
  full_name='SinFloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='min', full_name='SinFloatFunctionConfig.min', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='max', full_name='SinFloatFunctionConfig.max', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='phase', full_name='SinFloatFunctionConfig.phase', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='repeats', full_name='SinFloatFunctionConfig.repeats', index=3,
      number=4, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=124,
  serialized_end=206,
)


_STEPSFLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='StepsFloatFunctionConfig',
  full_name='StepsFloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='num_steps', full_name='StepsFloatFunctionConfig.num_steps', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='diff_per_step', full_name='StepsFloatFunctionConfig.diff_per_step', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='first_step_value', full_name='StepsFloatFunctionConfig.first_step_value', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=208,
  serialized_end=302,
)


_REPEATFLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='RepeatFloatFunctionConfig',
  full_name='RepeatFloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='numberOfTimes', full_name='RepeatFloatFunctionConfig.numberOfTimes', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='funcToRepeat', full_name='RepeatFloatFunctionConfig.funcToRepeat', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=304,
  serialized_end=392,
)


_HALFFLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='HalfFloatFunctionConfig',
  full_name='HalfFloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='f1', full_name='HalfFloatFunctionConfig.f1', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='f2', full_name='HalfFloatFunctionConfig.f2', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=394,
  serialized_end=475,
)


_COMB2FLOATFUNCTIONCONFIG = _descriptor.Descriptor(
  name='Comb2FloatFunctionConfig',
  full_name='Comb2FloatFunctionConfig',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='f1', full_name='Comb2FloatFunctionConfig.f1', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='amount1', full_name='Comb2FloatFunctionConfig.amount1', index=1,
      number=2, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='f2', full_name='Comb2FloatFunctionConfig.f2', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='amount2', full_name='Comb2FloatFunctionConfig.amount2', index=3,
      number=4, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=477,
  serialized_end=593,
)


_FLOATFUNCTION = _descriptor.Descriptor(
  name='FloatFunction',
  full_name='FloatFunction',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='const_value', full_name='FloatFunction.const_value', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='linear', full_name='FloatFunction.linear', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sin', full_name='FloatFunction.sin', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='steps', full_name='FloatFunction.steps', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='repeat', full_name='FloatFunction.repeat', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='half', full_name='FloatFunction.half', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='comb2', full_name='FloatFunction.comb2', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='function', full_name='FloatFunction.function',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=596,
  serialized_end=940,
)

_REPEATFLOATFUNCTIONCONFIG.fields_by_name['funcToRepeat'].message_type = _FLOATFUNCTION
_HALFFLOATFUNCTIONCONFIG.fields_by_name['f1'].message_type = _FLOATFUNCTION
_HALFFLOATFUNCTIONCONFIG.fields_by_name['f2'].message_type = _FLOATFUNCTION
_COMB2FLOATFUNCTIONCONFIG.fields_by_name['f1'].message_type = _FLOATFUNCTION
_COMB2FLOATFUNCTIONCONFIG.fields_by_name['f2'].message_type = _FLOATFUNCTION
_FLOATFUNCTION.fields_by_name['const_value'].message_type = _CONSTVALUEFLOATFUNCTIONCONFIG
_FLOATFUNCTION.fields_by_name['linear'].message_type = _LINEARFLOATFUNCTIONCONFIG
_FLOATFUNCTION.fields_by_name['sin'].message_type = _SINFLOATFUNCTIONCONFIG
_FLOATFUNCTION.fields_by_name['steps'].message_type = _STEPSFLOATFUNCTIONCONFIG
_FLOATFUNCTION.fields_by_name['repeat'].message_type = _REPEATFLOATFUNCTIONCONFIG
_FLOATFUNCTION.fields_by_name['half'].message_type = _HALFFLOATFUNCTIONCONFIG
_FLOATFUNCTION.fields_by_name['comb2'].message_type = _COMB2FLOATFUNCTIONCONFIG
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['const_value'])
_FLOATFUNCTION.fields_by_name['const_value'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['linear'])
_FLOATFUNCTION.fields_by_name['linear'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['sin'])
_FLOATFUNCTION.fields_by_name['sin'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['steps'])
_FLOATFUNCTION.fields_by_name['steps'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['repeat'])
_FLOATFUNCTION.fields_by_name['repeat'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['half'])
_FLOATFUNCTION.fields_by_name['half'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
_FLOATFUNCTION.oneofs_by_name['function'].fields.append(
  _FLOATFUNCTION.fields_by_name['comb2'])
_FLOATFUNCTION.fields_by_name['comb2'].containing_oneof = _FLOATFUNCTION.oneofs_by_name['function']
DESCRIPTOR.message_types_by_name['ConstValueFloatFunctionConfig'] = _CONSTVALUEFLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['LinearFloatFunctionConfig'] = _LINEARFLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['SinFloatFunctionConfig'] = _SINFLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['StepsFloatFunctionConfig'] = _STEPSFLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['RepeatFloatFunctionConfig'] = _REPEATFLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['HalfFloatFunctionConfig'] = _HALFFLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['Comb2FloatFunctionConfig'] = _COMB2FLOATFUNCTIONCONFIG
DESCRIPTOR.message_types_by_name['FloatFunction'] = _FLOATFUNCTION

ConstValueFloatFunctionConfig = _reflection.GeneratedProtocolMessageType('ConstValueFloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _CONSTVALUEFLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:ConstValueFloatFunctionConfig)
  ))
_sym_db.RegisterMessage(ConstValueFloatFunctionConfig)

LinearFloatFunctionConfig = _reflection.GeneratedProtocolMessageType('LinearFloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _LINEARFLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:LinearFloatFunctionConfig)
  ))
_sym_db.RegisterMessage(LinearFloatFunctionConfig)

SinFloatFunctionConfig = _reflection.GeneratedProtocolMessageType('SinFloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _SINFLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:SinFloatFunctionConfig)
  ))
_sym_db.RegisterMessage(SinFloatFunctionConfig)

StepsFloatFunctionConfig = _reflection.GeneratedProtocolMessageType('StepsFloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _STEPSFLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:StepsFloatFunctionConfig)
  ))
_sym_db.RegisterMessage(StepsFloatFunctionConfig)

RepeatFloatFunctionConfig = _reflection.GeneratedProtocolMessageType('RepeatFloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _REPEATFLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:RepeatFloatFunctionConfig)
  ))
_sym_db.RegisterMessage(RepeatFloatFunctionConfig)

HalfFloatFunctionConfig = _reflection.GeneratedProtocolMessageType('HalfFloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _HALFFLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:HalfFloatFunctionConfig)
  ))
_sym_db.RegisterMessage(HalfFloatFunctionConfig)

Comb2FloatFunctionConfig = _reflection.GeneratedProtocolMessageType('Comb2FloatFunctionConfig', (_message.Message,), dict(
  DESCRIPTOR = _COMB2FLOATFUNCTIONCONFIG,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:Comb2FloatFunctionConfig)
  ))
_sym_db.RegisterMessage(Comb2FloatFunctionConfig)

FloatFunction = _reflection.GeneratedProtocolMessageType('FloatFunction', (_message.Message,), dict(
  DESCRIPTOR = _FLOATFUNCTION,
  __module__ = 'functions_pb2'
  # @@protoc_insertion_point(class_scope:FloatFunction)
  ))
_sym_db.RegisterMessage(FloatFunction)


# @@protoc_insertion_point(module_scope)
