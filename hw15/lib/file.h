#ifndef FILE_H
#define FILE_H

#include <memory>
#include <cassert>
#include "lib/directory.h"
#include "lib/fs_element.h"

namespace fs {

class File final : public FSElement, public std::enable_shared_from_this<File> {
 public:
  File(const std::shared_ptr<Directory>& parent, const std::string& name,
       const std::string& owner, unsigned int size)
      : FSElement(parent, name, owner) {
    size_ = size;
  }
  bool isFile() const { return true; }
  void setSize(unsigned int size) { size_ = size; }
  unsigned int getSize() const { return size_; }
  void accept(FSVisitor& v) { v.visit(shared_from_this()); }
  unsigned int getDiskUtil() const { return size_; }
};

}  // end of namespace fs

#endif  // FILE_H
