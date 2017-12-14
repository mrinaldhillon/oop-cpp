#include "lib/directory.h"
#include <cassert>

namespace fs {

Directory::Directory(const std::shared_ptr<Directory>& parent, const std::string& name,
                     const std::string& owner)
    : FSElement(parent, name, owner), children_{} {}

const std::vector<std::shared_ptr<FSElement>> Directory::getChildren() const {
  return children_;
}

void Directory::appendChild(std::shared_ptr<FSElement> child) {
    children_.push_back(child);
    last_modified_ = std::time(nullptr);
}

bool Directory::isFile() const { return false; }

void Directory::setSize(unsigned int) {
  static_assert("Director::setSize is not allowed");
}

unsigned int Directory::getSizeOfChildrenRecursive(
    const std::vector<std::shared_ptr<FSElement>> children) const {
  unsigned int total_size = 0;
  for (auto child : children) {
    if (false == child->isFile()) {
      total_size += getSizeOfChildrenRecursive(child->getChildren());
    } else
      total_size += child->getSize();
  }
  return total_size;
}

unsigned int Directory::getSize() const {
  return getSizeOfChildrenRecursive(getChildren());
}

}  // end of namespace fs
