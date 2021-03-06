/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef services_TYPES_H
#define services_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




typedef int8_t version_t;

typedef int64_t time_t_def;

class File;

typedef struct _File__isset {
  _File__isset() : creation(false), modification(false), version(false), name(false), content(false) {}
  bool creation :1;
  bool modification :1;
  bool version :1;
  bool name :1;
  bool content :1;
} _File__isset;

class File {
 public:

  File(const File&);
  File& operator=(const File&);
  File() : creation(0), modification(0), version(0), name(), content() {
  }

  virtual ~File() throw();
  time_t_def creation;
  time_t_def modification;
  version_t version;
  std::string name;
  std::string content;

  _File__isset __isset;

  void __set_creation(const time_t_def val);

  void __set_modification(const time_t_def val);

  void __set_version(const version_t val);

  void __set_name(const std::string& val);

  void __set_content(const std::string& val);

  bool operator == (const File & rhs) const
  {
    if (!(creation == rhs.creation))
      return false;
    if (!(modification == rhs.modification))
      return false;
    if (!(version == rhs.version))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(content == rhs.content))
      return false;
    return true;
  }
  bool operator != (const File &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const File & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(File &a, File &b);

inline std::ostream& operator<<(std::ostream& out, const File& obj)
{
  obj.printTo(out);
  return out;
}



#endif
