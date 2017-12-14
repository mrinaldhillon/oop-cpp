#include "lib/directory.h"
#include <cassert>

namespace fs {

Directory::Directory(std::shared_ptr<FSElement> parent, const std::string& name,
                     const std::string& owner)
    : FSElement(parent, name, owner), children_{} {}

const std::vector<std::shared_ptr<FSElement>> Directory::getChildren() const {
  return children_;
}

void Directory::appendChild(std::shared_ptr<FSElement> child) {
  assert(nullptr != child);
  children_.push_back(child);
  last_modified_ = std::time(nullptr);
}

bool Directory::isFile() const { return false; }

void Directory::setSize(unsigned int) {
  static_assert("Director::setSize is not allowed");
}
#if 0
void Directory::get_size_of_children_recursive(
    const std::vector<std::shared_ptr<FSElement>> children,
    unsigned int& total_size) const {
  for (auto child : children) {
    total_size += child->getSize();
    if (false == child->isFile()) {
      get_size_of_children_recursive(child->getChildren(), total_size);
    }
  }
}

unsigned int Directory::getSize() const {
  unsigned int total_size = 0;
  get_size_of_children_recursive(getChildren(), total_size);
  return total_size;
}
#endif
unsigned int Directory::getSizeOfChildrenRecursive(
    const std::vector<std::shared_ptr<FSElement>> children) const {
  unsigned int total_size = 0;
  for (auto child : children) {
    if (false == child->isFile()) {
      total_size += getSizeOfChildrenRecursive(child->getChildren());
    } else total_size += child->getSize();
  }
  return total_size;
}

unsigned int Directory::getSize() const {
  return getSizeOfChildrenRecursive(getChildren());
}

}  // end of namespace fs
