#include "lib/link.h"
#include <sstream>
#include <string>

namespace fs {

Link::Link(const std::shared_ptr<Directory>& parent, const std::string& name,
           const std::string& owner, const std::shared_ptr<FSElement>& target)
    : FSElement(parent, name, owner), target_(target) {
  size_ = 0;
}

bool Link::isFile() const { return true; }

unsigned int Link::getTargetSize() const {
  auto target_spt = target_.lock();
  return target_spt->getSize();
}

unsigned int Link::getSize() const { return size_; }

void Link::accept(FSVisitor& v) { v.visit(shared_from_this()); }

unsigned int Link::getDiskUtil() const { return size_; }
std::string Link::getInfo() const {
  //	TODO: implement get path to get target's absolute path
  std::ostringstream oss;

  if (auto target = target_.lock()) {
    oss << "link\t" << getName() << " -> " << target->getInfo();
  } else {
    auto mod_time = getModTime();
    oss << "link\t" << getOwner() << "\t" << getSize() << "\t"
        << std::asctime(std::localtime(&mod_time)) << "\t" << getName()
        << " -> ";
  }
  return oss.str();
}

}  // end of namespace fs
