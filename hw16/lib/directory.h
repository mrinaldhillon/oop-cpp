#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <memory>
#include <vector>
#include "lib/fs_element.h"

namespace fs {

class Directory final : public FSElement,
                        public std::enable_shared_from_this<Directory> {
 private:
  std::vector<std::shared_ptr<FSElement>> children_;
  unsigned int getSizeOfChildrenRecursive(
      const std::vector<std::shared_ptr<FSElement>> children) const;

 public:
  Directory(const std::shared_ptr<Directory>& parent, const std::string& name,
            const std::string& owner);
  // Directory(const Directory& rhs);
  // Directory& operator=(const Directory& rhs);

  bool isFile() const;
  const std::vector<std::shared_ptr<FSElement>> getChildren() const;
  void appendChild(std::shared_ptr<FSElement> child);
  unsigned int getSize() const;
  void accept(FSVisitor&);
  unsigned int getDiskUtil() const;
  void addChild(std::shared_ptr<FSElement> child, int index);
  std::string getInfo() const;
  void rmChild(
      const std::string& name);  // throws range_error of element not found
};

}  // end of namespace fs

#endif  // DIRECTORY_H
