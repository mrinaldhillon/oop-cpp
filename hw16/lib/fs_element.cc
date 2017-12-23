#include "lib/fs_element.h"
#include <cassert>
#include <ctime>

namespace fs {

FSElement::FSElement(const std::shared_ptr<Directory>& parent,
                     const std::string& name, const std::string& owner)
    : parent_(parent),
      name_(name),
      owner_(owner),
      created_(std::time(nullptr)),
      last_modified_(created_),
      size_(0) {
  if (nullptr == parent)
    assert(name == "/");  // TBD: should these be runtime exception?
}

std::weak_ptr<Directory> FSElement::getParent() const { return parent_; }
void FSElement::setParent(const std::shared_ptr<Directory>& parent) {
  parent_ = parent;
  last_modified_ = std::time(nullptr);
}
const std::string& FSElement::getName() const { return name_; }
void FSElement::setName(const std::string& name) { name_ = name; }
const std::string& FSElement::getOwner() const { return owner_; }
void FSElement::setOwner(const std::string& owner) { owner_ = owner; }
std::time_t FSElement::getModTime() const { return last_modified_; }
void FSElement::setModTime(const std::time_t& last_modified) {
  last_modified_ = last_modified;
}
std::time_t FSElement::getCreationTime() const { return created_; }

}  // end of namespace fs
