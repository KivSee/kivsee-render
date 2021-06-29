// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: segments.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_segments_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_segments_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_segments_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_segments_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_segments_2eproto;
class SegmentConfig;
class SegmentConfigDefaultTypeInternal;
extern SegmentConfigDefaultTypeInternal _SegmentConfig_default_instance_;
class SegmentsMapConfig;
class SegmentsMapConfigDefaultTypeInternal;
extern SegmentsMapConfigDefaultTypeInternal _SegmentsMapConfig_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::SegmentConfig* Arena::CreateMaybeMessage<::SegmentConfig>(Arena*);
template<> ::SegmentsMapConfig* Arena::CreateMaybeMessage<::SegmentsMapConfig>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class SegmentConfig PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SegmentConfig) */ {
 public:
  inline SegmentConfig() : SegmentConfig(nullptr) {}
  virtual ~SegmentConfig();

  SegmentConfig(const SegmentConfig& from);
  SegmentConfig(SegmentConfig&& from) noexcept
    : SegmentConfig() {
    *this = ::std::move(from);
  }

  inline SegmentConfig& operator=(const SegmentConfig& from) {
    CopyFrom(from);
    return *this;
  }
  inline SegmentConfig& operator=(SegmentConfig&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const SegmentConfig& default_instance();

  static inline const SegmentConfig* internal_default_instance() {
    return reinterpret_cast<const SegmentConfig*>(
               &_SegmentConfig_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SegmentConfig& a, SegmentConfig& b) {
    a.Swap(&b);
  }
  inline void Swap(SegmentConfig* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SegmentConfig* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SegmentConfig* New() const final {
    return CreateMaybeMessage<SegmentConfig>(nullptr);
  }

  SegmentConfig* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SegmentConfig>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SegmentConfig& from);
  void MergeFrom(const SegmentConfig& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SegmentConfig* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SegmentConfig";
  }
  protected:
  explicit SegmentConfig(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_segments_2eproto);
    return ::descriptor_table_segments_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIndicesFieldNumber = 2,
    kNameFieldNumber = 1,
  };
  // repeated uint32 indices = 2;
  int indices_size() const;
  private:
  int _internal_indices_size() const;
  public:
  void clear_indices();
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_indices(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      _internal_indices() const;
  void _internal_add_indices(::PROTOBUF_NAMESPACE_ID::uint32 value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      _internal_mutable_indices();
  public:
  ::PROTOBUF_NAMESPACE_ID::uint32 indices(int index) const;
  void set_indices(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_indices(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      indices() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_indices();

  // string name = 1;
  void clear_name();
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // @@protoc_insertion_point(class_scope:SegmentConfig)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > indices_;
  mutable std::atomic<int> _indices_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_segments_2eproto;
};
// -------------------------------------------------------------------

class SegmentsMapConfig PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:SegmentsMapConfig) */ {
 public:
  inline SegmentsMapConfig() : SegmentsMapConfig(nullptr) {}
  virtual ~SegmentsMapConfig();

  SegmentsMapConfig(const SegmentsMapConfig& from);
  SegmentsMapConfig(SegmentsMapConfig&& from) noexcept
    : SegmentsMapConfig() {
    *this = ::std::move(from);
  }

  inline SegmentsMapConfig& operator=(const SegmentsMapConfig& from) {
    CopyFrom(from);
    return *this;
  }
  inline SegmentsMapConfig& operator=(SegmentsMapConfig&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const SegmentsMapConfig& default_instance();

  static inline const SegmentsMapConfig* internal_default_instance() {
    return reinterpret_cast<const SegmentsMapConfig*>(
               &_SegmentsMapConfig_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SegmentsMapConfig& a, SegmentsMapConfig& b) {
    a.Swap(&b);
  }
  inline void Swap(SegmentsMapConfig* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SegmentsMapConfig* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SegmentsMapConfig* New() const final {
    return CreateMaybeMessage<SegmentsMapConfig>(nullptr);
  }

  SegmentsMapConfig* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SegmentsMapConfig>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SegmentsMapConfig& from);
  void MergeFrom(const SegmentsMapConfig& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SegmentsMapConfig* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "SegmentsMapConfig";
  }
  protected:
  explicit SegmentsMapConfig(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_segments_2eproto);
    return ::descriptor_table_segments_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSegmentsFieldNumber = 3,
    kGuidFieldNumber = 1,
    kNumberOfPixelsFieldNumber = 2,
  };
  // repeated .SegmentConfig segments = 3;
  int segments_size() const;
  private:
  int _internal_segments_size() const;
  public:
  void clear_segments();
  ::SegmentConfig* mutable_segments(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::SegmentConfig >*
      mutable_segments();
  private:
  const ::SegmentConfig& _internal_segments(int index) const;
  ::SegmentConfig* _internal_add_segments();
  public:
  const ::SegmentConfig& segments(int index) const;
  ::SegmentConfig* add_segments();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::SegmentConfig >&
      segments() const;

  // fixed32 guid = 1;
  void clear_guid();
  ::PROTOBUF_NAMESPACE_ID::uint32 guid() const;
  void set_guid(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_guid() const;
  void _internal_set_guid(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // uint32 number_of_pixels = 2;
  void clear_number_of_pixels();
  ::PROTOBUF_NAMESPACE_ID::uint32 number_of_pixels() const;
  void set_number_of_pixels(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_number_of_pixels() const;
  void _internal_set_number_of_pixels(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:SegmentsMapConfig)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::SegmentConfig > segments_;
  ::PROTOBUF_NAMESPACE_ID::uint32 guid_;
  ::PROTOBUF_NAMESPACE_ID::uint32 number_of_pixels_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_segments_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SegmentConfig

// string name = 1;
inline void SegmentConfig::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& SegmentConfig::name() const {
  // @@protoc_insertion_point(field_get:SegmentConfig.name)
  return _internal_name();
}
inline void SegmentConfig::set_name(const std::string& value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:SegmentConfig.name)
}
inline std::string* SegmentConfig::mutable_name() {
  // @@protoc_insertion_point(field_mutable:SegmentConfig.name)
  return _internal_mutable_name();
}
inline const std::string& SegmentConfig::_internal_name() const {
  return name_.Get();
}
inline void SegmentConfig::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void SegmentConfig::set_name(std::string&& value) {
  
  name_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:SegmentConfig.name)
}
inline void SegmentConfig::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:SegmentConfig.name)
}
inline void SegmentConfig::set_name(const char* value,
    size_t size) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:SegmentConfig.name)
}
inline std::string* SegmentConfig::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* SegmentConfig::release_name() {
  // @@protoc_insertion_point(field_release:SegmentConfig.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void SegmentConfig::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:SegmentConfig.name)
}

// repeated uint32 indices = 2;
inline int SegmentConfig::_internal_indices_size() const {
  return indices_.size();
}
inline int SegmentConfig::indices_size() const {
  return _internal_indices_size();
}
inline void SegmentConfig::clear_indices() {
  indices_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SegmentConfig::_internal_indices(int index) const {
  return indices_.Get(index);
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SegmentConfig::indices(int index) const {
  // @@protoc_insertion_point(field_get:SegmentConfig.indices)
  return _internal_indices(index);
}
inline void SegmentConfig::set_indices(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  indices_.Set(index, value);
  // @@protoc_insertion_point(field_set:SegmentConfig.indices)
}
inline void SegmentConfig::_internal_add_indices(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  indices_.Add(value);
}
inline void SegmentConfig::add_indices(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_add_indices(value);
  // @@protoc_insertion_point(field_add:SegmentConfig.indices)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
SegmentConfig::_internal_indices() const {
  return indices_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
SegmentConfig::indices() const {
  // @@protoc_insertion_point(field_list:SegmentConfig.indices)
  return _internal_indices();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
SegmentConfig::_internal_mutable_indices() {
  return &indices_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
SegmentConfig::mutable_indices() {
  // @@protoc_insertion_point(field_mutable_list:SegmentConfig.indices)
  return _internal_mutable_indices();
}

// -------------------------------------------------------------------

// SegmentsMapConfig

// fixed32 guid = 1;
inline void SegmentsMapConfig::clear_guid() {
  guid_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SegmentsMapConfig::_internal_guid() const {
  return guid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SegmentsMapConfig::guid() const {
  // @@protoc_insertion_point(field_get:SegmentsMapConfig.guid)
  return _internal_guid();
}
inline void SegmentsMapConfig::_internal_set_guid(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  guid_ = value;
}
inline void SegmentsMapConfig::set_guid(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_guid(value);
  // @@protoc_insertion_point(field_set:SegmentsMapConfig.guid)
}

// uint32 number_of_pixels = 2;
inline void SegmentsMapConfig::clear_number_of_pixels() {
  number_of_pixels_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SegmentsMapConfig::_internal_number_of_pixels() const {
  return number_of_pixels_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 SegmentsMapConfig::number_of_pixels() const {
  // @@protoc_insertion_point(field_get:SegmentsMapConfig.number_of_pixels)
  return _internal_number_of_pixels();
}
inline void SegmentsMapConfig::_internal_set_number_of_pixels(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  number_of_pixels_ = value;
}
inline void SegmentsMapConfig::set_number_of_pixels(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_number_of_pixels(value);
  // @@protoc_insertion_point(field_set:SegmentsMapConfig.number_of_pixels)
}

// repeated .SegmentConfig segments = 3;
inline int SegmentsMapConfig::_internal_segments_size() const {
  return segments_.size();
}
inline int SegmentsMapConfig::segments_size() const {
  return _internal_segments_size();
}
inline void SegmentsMapConfig::clear_segments() {
  segments_.Clear();
}
inline ::SegmentConfig* SegmentsMapConfig::mutable_segments(int index) {
  // @@protoc_insertion_point(field_mutable:SegmentsMapConfig.segments)
  return segments_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::SegmentConfig >*
SegmentsMapConfig::mutable_segments() {
  // @@protoc_insertion_point(field_mutable_list:SegmentsMapConfig.segments)
  return &segments_;
}
inline const ::SegmentConfig& SegmentsMapConfig::_internal_segments(int index) const {
  return segments_.Get(index);
}
inline const ::SegmentConfig& SegmentsMapConfig::segments(int index) const {
  // @@protoc_insertion_point(field_get:SegmentsMapConfig.segments)
  return _internal_segments(index);
}
inline ::SegmentConfig* SegmentsMapConfig::_internal_add_segments() {
  return segments_.Add();
}
inline ::SegmentConfig* SegmentsMapConfig::add_segments() {
  // @@protoc_insertion_point(field_add:SegmentsMapConfig.segments)
  return _internal_add_segments();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::SegmentConfig >&
SegmentsMapConfig::segments() const {
  // @@protoc_insertion_point(field_list:SegmentsMapConfig.segments)
  return segments_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_segments_2eproto
