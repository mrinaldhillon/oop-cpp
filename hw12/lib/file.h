#ifndef FILE_H
#define FILE_H

#include "lib/fs_element.h"

namespace fs {

class File final : public FSElement {
 public:
  File(std::shared_ptr<FSElement> parent, const std::string& name,
       const std::string& owner, unsigned int size)
      : FSElement(parent, name, owner) {
    size_ = size;
  }

  bool isFile() const { return true; }
  const std::vector<std::shared_ptr<FSElement>> getChildren() const {
    static_assert("File::getChildren is not allowed");
    return std::vector<std::shared_ptr<FSElement>>{};
  }

  void appendChild(std::shared_ptr<FSElement>) {
    static_assert("File::appendChild is not allowed");
  }
};

}  // end of namespace fs

#endif  // FILE_H
