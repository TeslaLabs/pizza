// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: data.proto

#ifndef PROTOBUF_data_2eproto__INCLUDED
#define PROTOBUF_data_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_data_2eproto();
void protobuf_InitDefaults_data_2eproto();
void protobuf_AssignDesc_data_2eproto();
void protobuf_ShutdownFile_data_2eproto();

class Data;
class Mesh;
class Mesh_Face;
class Mesh_Vertex;
class Shader;

// ===================================================================

class Mesh_Vertex : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Mesh.Vertex) */ {
 public:
  Mesh_Vertex();
  virtual ~Mesh_Vertex();

  Mesh_Vertex(const Mesh_Vertex& from);

  inline Mesh_Vertex& operator=(const Mesh_Vertex& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Mesh_Vertex& default_instance();

  static const Mesh_Vertex* internal_default_instance();

  void Swap(Mesh_Vertex* other);

  // implements Message ----------------------------------------------

  inline Mesh_Vertex* New() const { return New(NULL); }

  Mesh_Vertex* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Mesh_Vertex& from);
  void MergeFrom(const Mesh_Vertex& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Mesh_Vertex* other);
  void UnsafeMergeFrom(const Mesh_Vertex& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional float x = 1;
  void clear_x();
  static const int kXFieldNumber = 1;
  float x() const;
  void set_x(float value);

  // optional float y = 2;
  void clear_y();
  static const int kYFieldNumber = 2;
  float y() const;
  void set_y(float value);

  // optional float z = 3;
  void clear_z();
  static const int kZFieldNumber = 3;
  float z() const;
  void set_z(float value);

  // optional float i = 4;
  void clear_i();
  static const int kIFieldNumber = 4;
  float i() const;
  void set_i(float value);

  // optional float j = 5;
  void clear_j();
  static const int kJFieldNumber = 5;
  float j() const;
  void set_j(float value);

  // optional float k = 7;
  void clear_k();
  static const int kKFieldNumber = 7;
  float k() const;
  void set_k(float value);

  // optional float u = 8;
  void clear_u();
  static const int kUFieldNumber = 8;
  float u() const;
  void set_u(float value);

  // optional float v = 9;
  void clear_v();
  static const int kVFieldNumber = 9;
  float v() const;
  void set_v(float value);

  // @@protoc_insertion_point(class_scope:Mesh.Vertex)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float x_;
  float y_;
  float z_;
  float i_;
  float j_;
  float k_;
  float u_;
  float v_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_data_2eproto_impl();
  friend void  protobuf_AddDesc_data_2eproto_impl();
  friend void protobuf_AssignDesc_data_2eproto();
  friend void protobuf_ShutdownFile_data_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Mesh_Vertex> Mesh_Vertex_default_instance_;

// -------------------------------------------------------------------

class Mesh_Face : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Mesh.Face) */ {
 public:
  Mesh_Face();
  virtual ~Mesh_Face();

  Mesh_Face(const Mesh_Face& from);

  inline Mesh_Face& operator=(const Mesh_Face& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Mesh_Face& default_instance();

  static const Mesh_Face* internal_default_instance();

  void Swap(Mesh_Face* other);

  // implements Message ----------------------------------------------

  inline Mesh_Face* New() const { return New(NULL); }

  Mesh_Face* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Mesh_Face& from);
  void MergeFrom(const Mesh_Face& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Mesh_Face* other);
  void UnsafeMergeFrom(const Mesh_Face& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 a = 1;
  void clear_a();
  static const int kAFieldNumber = 1;
  ::google::protobuf::uint32 a() const;
  void set_a(::google::protobuf::uint32 value);

  // optional uint32 b = 2;
  void clear_b();
  static const int kBFieldNumber = 2;
  ::google::protobuf::uint32 b() const;
  void set_b(::google::protobuf::uint32 value);

  // optional uint32 c = 3;
  void clear_c();
  static const int kCFieldNumber = 3;
  ::google::protobuf::uint32 c() const;
  void set_c(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Mesh.Face)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 a_;
  ::google::protobuf::uint32 b_;
  ::google::protobuf::uint32 c_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_data_2eproto_impl();
  friend void  protobuf_AddDesc_data_2eproto_impl();
  friend void protobuf_AssignDesc_data_2eproto();
  friend void protobuf_ShutdownFile_data_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Mesh_Face> Mesh_Face_default_instance_;

// -------------------------------------------------------------------

class Mesh : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Mesh) */ {
 public:
  Mesh();
  virtual ~Mesh();

  Mesh(const Mesh& from);

  inline Mesh& operator=(const Mesh& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Mesh& default_instance();

  static const Mesh* internal_default_instance();

  void Swap(Mesh* other);

  // implements Message ----------------------------------------------

  inline Mesh* New() const { return New(NULL); }

  Mesh* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Mesh& from);
  void MergeFrom(const Mesh& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Mesh* other);
  void UnsafeMergeFrom(const Mesh& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Mesh_Vertex Vertex;
  typedef Mesh_Face Face;

  // accessors -------------------------------------------------------

  // optional string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // repeated .Mesh.Vertex vertex = 2;
  int vertex_size() const;
  void clear_vertex();
  static const int kVertexFieldNumber = 2;
  const ::Mesh_Vertex& vertex(int index) const;
  ::Mesh_Vertex* mutable_vertex(int index);
  ::Mesh_Vertex* add_vertex();
  ::google::protobuf::RepeatedPtrField< ::Mesh_Vertex >*
      mutable_vertex();
  const ::google::protobuf::RepeatedPtrField< ::Mesh_Vertex >&
      vertex() const;

  // repeated .Mesh.Face face = 3;
  int face_size() const;
  void clear_face();
  static const int kFaceFieldNumber = 3;
  const ::Mesh_Face& face(int index) const;
  ::Mesh_Face* mutable_face(int index);
  ::Mesh_Face* add_face();
  ::google::protobuf::RepeatedPtrField< ::Mesh_Face >*
      mutable_face();
  const ::google::protobuf::RepeatedPtrField< ::Mesh_Face >&
      face() const;

  // @@protoc_insertion_point(class_scope:Mesh)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::Mesh_Vertex > vertex_;
  ::google::protobuf::RepeatedPtrField< ::Mesh_Face > face_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_data_2eproto_impl();
  friend void  protobuf_AddDesc_data_2eproto_impl();
  friend void protobuf_AssignDesc_data_2eproto();
  friend void protobuf_ShutdownFile_data_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Mesh> Mesh_default_instance_;

// -------------------------------------------------------------------

class Shader : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Shader) */ {
 public:
  Shader();
  virtual ~Shader();

  Shader(const Shader& from);

  inline Shader& operator=(const Shader& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Shader& default_instance();

  static const Shader* internal_default_instance();

  void Swap(Shader* other);

  // implements Message ----------------------------------------------

  inline Shader* New() const { return New(NULL); }

  Shader* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Shader& from);
  void MergeFrom(const Shader& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Shader* other);
  void UnsafeMergeFrom(const Shader& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  const ::std::string& type() const;
  void set_type(const ::std::string& value);
  void set_type(const char* value);
  void set_type(const char* value, size_t size);
  ::std::string* mutable_type();
  ::std::string* release_type();
  void set_allocated_type(::std::string* type);

  // optional string name = 2;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional string source = 3;
  void clear_source();
  static const int kSourceFieldNumber = 3;
  const ::std::string& source() const;
  void set_source(const ::std::string& value);
  void set_source(const char* value);
  void set_source(const char* value, size_t size);
  ::std::string* mutable_source();
  ::std::string* release_source();
  void set_allocated_source(::std::string* source);

  // @@protoc_insertion_point(class_scope:Shader)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr type_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr source_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_data_2eproto_impl();
  friend void  protobuf_AddDesc_data_2eproto_impl();
  friend void protobuf_AssignDesc_data_2eproto();
  friend void protobuf_ShutdownFile_data_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Shader> Shader_default_instance_;

// -------------------------------------------------------------------

class Data : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Data) */ {
 public:
  Data();
  virtual ~Data();

  Data(const Data& from);

  inline Data& operator=(const Data& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Data& default_instance();

  static const Data* internal_default_instance();

  void Swap(Data* other);

  // implements Message ----------------------------------------------

  inline Data* New() const { return New(NULL); }

  Data* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Data& from);
  void MergeFrom(const Data& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Data* other);
  void UnsafeMergeFrom(const Data& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .Mesh mesh = 1;
  int mesh_size() const;
  void clear_mesh();
  static const int kMeshFieldNumber = 1;
  const ::Mesh& mesh(int index) const;
  ::Mesh* mutable_mesh(int index);
  ::Mesh* add_mesh();
  ::google::protobuf::RepeatedPtrField< ::Mesh >*
      mutable_mesh();
  const ::google::protobuf::RepeatedPtrField< ::Mesh >&
      mesh() const;

  // repeated .Shader shader = 2;
  int shader_size() const;
  void clear_shader();
  static const int kShaderFieldNumber = 2;
  const ::Shader& shader(int index) const;
  ::Shader* mutable_shader(int index);
  ::Shader* add_shader();
  ::google::protobuf::RepeatedPtrField< ::Shader >*
      mutable_shader();
  const ::google::protobuf::RepeatedPtrField< ::Shader >&
      shader() const;

  // @@protoc_insertion_point(class_scope:Data)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::Mesh > mesh_;
  ::google::protobuf::RepeatedPtrField< ::Shader > shader_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_data_2eproto_impl();
  friend void  protobuf_AddDesc_data_2eproto_impl();
  friend void protobuf_AssignDesc_data_2eproto();
  friend void protobuf_ShutdownFile_data_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Data> Data_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Mesh_Vertex

// optional float x = 1;
inline void Mesh_Vertex::clear_x() {
  x_ = 0;
}
inline float Mesh_Vertex::x() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.x)
  return x_;
}
inline void Mesh_Vertex::set_x(float value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.x)
}

// optional float y = 2;
inline void Mesh_Vertex::clear_y() {
  y_ = 0;
}
inline float Mesh_Vertex::y() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.y)
  return y_;
}
inline void Mesh_Vertex::set_y(float value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.y)
}

// optional float z = 3;
inline void Mesh_Vertex::clear_z() {
  z_ = 0;
}
inline float Mesh_Vertex::z() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.z)
  return z_;
}
inline void Mesh_Vertex::set_z(float value) {
  
  z_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.z)
}

// optional float i = 4;
inline void Mesh_Vertex::clear_i() {
  i_ = 0;
}
inline float Mesh_Vertex::i() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.i)
  return i_;
}
inline void Mesh_Vertex::set_i(float value) {
  
  i_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.i)
}

// optional float j = 5;
inline void Mesh_Vertex::clear_j() {
  j_ = 0;
}
inline float Mesh_Vertex::j() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.j)
  return j_;
}
inline void Mesh_Vertex::set_j(float value) {
  
  j_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.j)
}

// optional float k = 7;
inline void Mesh_Vertex::clear_k() {
  k_ = 0;
}
inline float Mesh_Vertex::k() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.k)
  return k_;
}
inline void Mesh_Vertex::set_k(float value) {
  
  k_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.k)
}

// optional float u = 8;
inline void Mesh_Vertex::clear_u() {
  u_ = 0;
}
inline float Mesh_Vertex::u() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.u)
  return u_;
}
inline void Mesh_Vertex::set_u(float value) {
  
  u_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.u)
}

// optional float v = 9;
inline void Mesh_Vertex::clear_v() {
  v_ = 0;
}
inline float Mesh_Vertex::v() const {
  // @@protoc_insertion_point(field_get:Mesh.Vertex.v)
  return v_;
}
inline void Mesh_Vertex::set_v(float value) {
  
  v_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Vertex.v)
}

inline const Mesh_Vertex* Mesh_Vertex::internal_default_instance() {
  return &Mesh_Vertex_default_instance_.get();
}
// -------------------------------------------------------------------

// Mesh_Face

// optional uint32 a = 1;
inline void Mesh_Face::clear_a() {
  a_ = 0u;
}
inline ::google::protobuf::uint32 Mesh_Face::a() const {
  // @@protoc_insertion_point(field_get:Mesh.Face.a)
  return a_;
}
inline void Mesh_Face::set_a(::google::protobuf::uint32 value) {
  
  a_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Face.a)
}

// optional uint32 b = 2;
inline void Mesh_Face::clear_b() {
  b_ = 0u;
}
inline ::google::protobuf::uint32 Mesh_Face::b() const {
  // @@protoc_insertion_point(field_get:Mesh.Face.b)
  return b_;
}
inline void Mesh_Face::set_b(::google::protobuf::uint32 value) {
  
  b_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Face.b)
}

// optional uint32 c = 3;
inline void Mesh_Face::clear_c() {
  c_ = 0u;
}
inline ::google::protobuf::uint32 Mesh_Face::c() const {
  // @@protoc_insertion_point(field_get:Mesh.Face.c)
  return c_;
}
inline void Mesh_Face::set_c(::google::protobuf::uint32 value) {
  
  c_ = value;
  // @@protoc_insertion_point(field_set:Mesh.Face.c)
}

inline const Mesh_Face* Mesh_Face::internal_default_instance() {
  return &Mesh_Face_default_instance_.get();
}
// -------------------------------------------------------------------

// Mesh

// optional string name = 1;
inline void Mesh::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Mesh::name() const {
  // @@protoc_insertion_point(field_get:Mesh.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Mesh::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Mesh.name)
}
inline void Mesh::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Mesh.name)
}
inline void Mesh::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Mesh.name)
}
inline ::std::string* Mesh::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:Mesh.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Mesh::release_name() {
  // @@protoc_insertion_point(field_release:Mesh.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Mesh::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:Mesh.name)
}

// repeated .Mesh.Vertex vertex = 2;
inline int Mesh::vertex_size() const {
  return vertex_.size();
}
inline void Mesh::clear_vertex() {
  vertex_.Clear();
}
inline const ::Mesh_Vertex& Mesh::vertex(int index) const {
  // @@protoc_insertion_point(field_get:Mesh.vertex)
  return vertex_.Get(index);
}
inline ::Mesh_Vertex* Mesh::mutable_vertex(int index) {
  // @@protoc_insertion_point(field_mutable:Mesh.vertex)
  return vertex_.Mutable(index);
}
inline ::Mesh_Vertex* Mesh::add_vertex() {
  // @@protoc_insertion_point(field_add:Mesh.vertex)
  return vertex_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Mesh_Vertex >*
Mesh::mutable_vertex() {
  // @@protoc_insertion_point(field_mutable_list:Mesh.vertex)
  return &vertex_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Mesh_Vertex >&
Mesh::vertex() const {
  // @@protoc_insertion_point(field_list:Mesh.vertex)
  return vertex_;
}

// repeated .Mesh.Face face = 3;
inline int Mesh::face_size() const {
  return face_.size();
}
inline void Mesh::clear_face() {
  face_.Clear();
}
inline const ::Mesh_Face& Mesh::face(int index) const {
  // @@protoc_insertion_point(field_get:Mesh.face)
  return face_.Get(index);
}
inline ::Mesh_Face* Mesh::mutable_face(int index) {
  // @@protoc_insertion_point(field_mutable:Mesh.face)
  return face_.Mutable(index);
}
inline ::Mesh_Face* Mesh::add_face() {
  // @@protoc_insertion_point(field_add:Mesh.face)
  return face_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Mesh_Face >*
Mesh::mutable_face() {
  // @@protoc_insertion_point(field_mutable_list:Mesh.face)
  return &face_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Mesh_Face >&
Mesh::face() const {
  // @@protoc_insertion_point(field_list:Mesh.face)
  return face_;
}

inline const Mesh* Mesh::internal_default_instance() {
  return &Mesh_default_instance_.get();
}
// -------------------------------------------------------------------

// Shader

// optional string type = 1;
inline void Shader::clear_type() {
  type_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Shader::type() const {
  // @@protoc_insertion_point(field_get:Shader.type)
  return type_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Shader::set_type(const ::std::string& value) {
  
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Shader.type)
}
inline void Shader::set_type(const char* value) {
  
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Shader.type)
}
inline void Shader::set_type(const char* value, size_t size) {
  
  type_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Shader.type)
}
inline ::std::string* Shader::mutable_type() {
  
  // @@protoc_insertion_point(field_mutable:Shader.type)
  return type_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Shader::release_type() {
  // @@protoc_insertion_point(field_release:Shader.type)
  
  return type_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Shader::set_allocated_type(::std::string* type) {
  if (type != NULL) {
    
  } else {
    
  }
  type_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), type);
  // @@protoc_insertion_point(field_set_allocated:Shader.type)
}

// optional string name = 2;
inline void Shader::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Shader::name() const {
  // @@protoc_insertion_point(field_get:Shader.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Shader::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Shader.name)
}
inline void Shader::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Shader.name)
}
inline void Shader::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Shader.name)
}
inline ::std::string* Shader::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:Shader.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Shader::release_name() {
  // @@protoc_insertion_point(field_release:Shader.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Shader::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:Shader.name)
}

// optional string source = 3;
inline void Shader::clear_source() {
  source_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Shader::source() const {
  // @@protoc_insertion_point(field_get:Shader.source)
  return source_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Shader::set_source(const ::std::string& value) {
  
  source_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Shader.source)
}
inline void Shader::set_source(const char* value) {
  
  source_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Shader.source)
}
inline void Shader::set_source(const char* value, size_t size) {
  
  source_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Shader.source)
}
inline ::std::string* Shader::mutable_source() {
  
  // @@protoc_insertion_point(field_mutable:Shader.source)
  return source_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Shader::release_source() {
  // @@protoc_insertion_point(field_release:Shader.source)
  
  return source_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Shader::set_allocated_source(::std::string* source) {
  if (source != NULL) {
    
  } else {
    
  }
  source_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), source);
  // @@protoc_insertion_point(field_set_allocated:Shader.source)
}

inline const Shader* Shader::internal_default_instance() {
  return &Shader_default_instance_.get();
}
// -------------------------------------------------------------------

// Data

// repeated .Mesh mesh = 1;
inline int Data::mesh_size() const {
  return mesh_.size();
}
inline void Data::clear_mesh() {
  mesh_.Clear();
}
inline const ::Mesh& Data::mesh(int index) const {
  // @@protoc_insertion_point(field_get:Data.mesh)
  return mesh_.Get(index);
}
inline ::Mesh* Data::mutable_mesh(int index) {
  // @@protoc_insertion_point(field_mutable:Data.mesh)
  return mesh_.Mutable(index);
}
inline ::Mesh* Data::add_mesh() {
  // @@protoc_insertion_point(field_add:Data.mesh)
  return mesh_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Mesh >*
Data::mutable_mesh() {
  // @@protoc_insertion_point(field_mutable_list:Data.mesh)
  return &mesh_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Mesh >&
Data::mesh() const {
  // @@protoc_insertion_point(field_list:Data.mesh)
  return mesh_;
}

// repeated .Shader shader = 2;
inline int Data::shader_size() const {
  return shader_.size();
}
inline void Data::clear_shader() {
  shader_.Clear();
}
inline const ::Shader& Data::shader(int index) const {
  // @@protoc_insertion_point(field_get:Data.shader)
  return shader_.Get(index);
}
inline ::Shader* Data::mutable_shader(int index) {
  // @@protoc_insertion_point(field_mutable:Data.shader)
  return shader_.Mutable(index);
}
inline ::Shader* Data::add_shader() {
  // @@protoc_insertion_point(field_add:Data.shader)
  return shader_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Shader >*
Data::mutable_shader() {
  // @@protoc_insertion_point(field_mutable_list:Data.shader)
  return &shader_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Shader >&
Data::shader() const {
  // @@protoc_insertion_point(field_list:Data.shader)
  return shader_;
}

inline const Data* Data::internal_default_instance() {
  return &Data_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_data_2eproto__INCLUDED
