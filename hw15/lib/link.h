#ifndef LINK_H
#define LINK_H

#include "lib/directory.h"
#include "lib/fs_element.h"

namespace fs {

class Link final : public FSElement, public std::enable_shared_from_this<Link> {
 private:
  std::weak_ptr<FSElement> target_;

 public:
  Link(const std::shared_ptr<Directory>& parent, const std::string& name,
       const std::string& owner, const std::shared_ptr<FSElement>& target)
      : FSElement(parent, name, owner), target_(target) {
    size_ = 0;
  }
  bool isFile() const { return true; }
  unsigned int getTargetSize() const {
    auto target_spt = target_.lock();
    return target_spt->getSize();
  }
  unsigned int getSize() const { return size_; }
  void accept(FSVisitor& v) { v.visit(shared_from_this()); }
  unsigned int getDiskUtil() const { return size_; }
};

}  // end of namespace fs

#endif  // LINK_H
