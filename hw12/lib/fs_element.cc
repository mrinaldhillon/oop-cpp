#include "lib/fs_element.h"
#include <cassert>
#include <ctime>

namespace fs {

FSElement::FSElement(const std::shared_ptr<FSElement>& parent, const std::string& name,
                     const std::string& owner)
    : parent_(parent),
      name_(name),
      owner_(owner),
      created_(std::time(nullptr)),
      last_modified_(created_),
      size_(0) {
  if (nullptr == parent)
    assert(name == "/");  // TBD: should these be runtime errors.
  else
    assert(false == parent->isFile());
};

std::weak_ptr<FSElement> FSElement::getParent() const { return parent_; }
const std::string& FSElement::getName() const { return name_; }
const std::string& FSElement::getOwner() const { return owner_; }
const std::time_t& FSElement::getModTime() const { return last_modified_; }
void FSElement::setModTime(std::time_t& last_modified) {
  last_modified_ = last_modified;
}
const std::time_t& FSElement::getCreationTime() const { return created_; }
bool FSElement::isFile() const { return true; }
unsigned int FSElement::getSize() const { return size_; }
void FSElement::setSize(unsigned int size) { size_ = size; }

}  // end of namespace fs
