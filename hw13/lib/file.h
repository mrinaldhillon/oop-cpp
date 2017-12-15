#ifndef FILE_H
#define FILE_H

#include <cassert>
#include "lib/directory.h"
#include "lib/fs_element.h"

namespace fs {

class File final : public FSElement {
 public:
  File(const std::shared_ptr<Directory>& parent, const std::string& name,
       const std::string& owner, unsigned int size)
      : FSElement(parent, name, owner) {
    size_ = size;
  }
  bool isFile() const { return true; }
  void setSize(unsigned int size) { size_ = size; }
  unsigned int getSize() const { return size_; }
};

}  // end of namespace fs

#endif  // FILE_H
