#include "lib/directory.h"
#include <sstream>
#include <string>

namespace fs {

Directory::Directory(const std::shared_ptr<Directory>& parent,
                     const std::string& name, const std::string& owner)
    : FSElement(parent, name, owner), children_{} {
  size_ = 0;
}

/*Directory::Directory(const Directory& rhs) : FSElement(rhs.parent_, rhs.name_,
rhs.owner_), children_{} {
        size_ = rhs.size_;
        for (auto rhs.child : rhs->getChildren()) {
                auto lhs = std::make_shared()

        }

}
//  Directory& operator=(const Directory& rhs);
*/
const std::vector<std::shared_ptr<FSElement>> Directory::getChildren() const {
  return children_;
}

void Directory::appendChild(std::shared_ptr<FSElement> child) {
  children_.push_back(child);
  last_modified_ = std::time(nullptr);
}

bool Directory::isFile() const { return false; }

unsigned int Directory::getSizeOfChildrenRecursive(
    const std::vector<std::shared_ptr<FSElement>> children) const {
  unsigned int total_size = 0;
  for (auto child : children) {
    if (false == child->isFile()) {
      total_size += getSizeOfChildrenRecursive(
          std::dynamic_pointer_cast<Directory>(child)->getChildren());
    } else
      total_size += child->getSize();
  }
  return total_size;
}

unsigned int Directory::getSize() const {
  return getSizeOfChildrenRecursive(getChildren());
}

void Directory::accept(FSVisitor& v) {
  v.visit(shared_from_this());
  for (auto child : children_) {
    child->accept(v);
  }
}

unsigned int Directory::getDiskUtil() const { return size_; }

void Directory::addChild(std::shared_ptr<FSElement> child, int index) {
  auto iterator = children_.begin();
  children_.insert(iterator + index, child);
  last_modified_ = std::time(nullptr);
}

std::string Directory::getInfo() const {
  std::ostringstream oss;
  oss << "directory\t" << getSize() << "\t" << getOwner() << "\t" << getName();
  return oss.str();
}

void Directory::rmChild(const std::string& name) {
  int index = 0;
  for (auto child : children_) {
    if (name == child->getName()) {
      children_.erase(children_.begin() + index);
      return;
    }
    index++;
  }
}

}  // end of namespace fs
