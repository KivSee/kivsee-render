# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: segments.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0esegments.proto\x12\x0ckivsee.proto\"\'\n\x05Pixel\x12\r\n\x05index\x18\x01 \x01(\r\x12\x0f\n\x07rel_pos\x18\x02 \x01(\x02\"<\n\x07Segment\x12\x0c\n\x04name\x18\x01 \x01(\t\x12#\n\x06pixels\x18\x02 \x03(\x0b\x32\x13.kivsee.proto.Pixel\"`\n\rThingSegments\x12\x0c\n\x04guid\x18\x01 \x01(\x07\x12\x18\n\x10number_of_pixels\x18\x02 \x01(\r\x12\'\n\x08segments\x18\x03 \x03(\x0b\x32\x15.kivsee.proto.Segmentb\x06proto3')



_PIXEL = DESCRIPTOR.message_types_by_name['Pixel']
_SEGMENT = DESCRIPTOR.message_types_by_name['Segment']
_THINGSEGMENTS = DESCRIPTOR.message_types_by_name['ThingSegments']
Pixel = _reflection.GeneratedProtocolMessageType('Pixel', (_message.Message,), {
  'DESCRIPTOR' : _PIXEL,
  '__module__' : 'segments_pb2'
  # @@protoc_insertion_point(class_scope:kivsee.proto.Pixel)
  })
_sym_db.RegisterMessage(Pixel)

Segment = _reflection.GeneratedProtocolMessageType('Segment', (_message.Message,), {
  'DESCRIPTOR' : _SEGMENT,
  '__module__' : 'segments_pb2'
  # @@protoc_insertion_point(class_scope:kivsee.proto.Segment)
  })
_sym_db.RegisterMessage(Segment)

ThingSegments = _reflection.GeneratedProtocolMessageType('ThingSegments', (_message.Message,), {
  'DESCRIPTOR' : _THINGSEGMENTS,
  '__module__' : 'segments_pb2'
  # @@protoc_insertion_point(class_scope:kivsee.proto.ThingSegments)
  })
_sym_db.RegisterMessage(ThingSegments)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _PIXEL._serialized_start=32
  _PIXEL._serialized_end=71
  _SEGMENT._serialized_start=73
  _SEGMENT._serialized_end=133
  _THINGSEGMENTS._serialized_start=135
  _THINGSEGMENTS._serialized_end=231
# @@protoc_insertion_point(module_scope)
