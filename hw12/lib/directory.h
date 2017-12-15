#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <memory>
#include <vector>
#include "lib/fs_element.h"

namespace fs {

class Directory final : public FSElement {
 private:
  std::vector<std::shared_ptr<FSElement>> children_;
  unsigned int getSizeOfChildrenRecursive(
      const std::vector<std::shared_ptr<FSElement>> children) const;

 public:
  Directory(const std::shared_ptr<Directory>& parent, const std::string& name,
            const std::string& owner);
  bool isFile() const;
  const std::vector<std::shared_ptr<FSElement>> getChildren() const;
  void appendChild(std::shared_ptr<FSElement> child);
  unsigned int getSize() const;
};

}  // end of namespace fs

#endif  // DIRECTORY_H
