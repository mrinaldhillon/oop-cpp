#ifndef LINK_H
#define LINK_H

#include "lib/fs_element.h"

namespace fs {

class Link final : public FSElement, public std::enable_shared_from_this<Link> {
 private:
  std::weak_ptr<FSElement> target_;

 public:
  Link(const std::shared_ptr<Directory>& parent, const std::string& name,
       const std::string& owner, const std::shared_ptr<FSElement>& target);
  bool isFile() const;
  unsigned int getTargetSize() const;
  unsigned int getSize() const;
  void accept(FSVisitor& v);
  unsigned int getDiskUtil() const;
  std::string getInfo() const;
};

}  // end of namespace fs

#endif  // LINK_H
