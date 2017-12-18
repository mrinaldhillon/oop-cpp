#ifndef FILE_H
#define FILE_H

#include "lib/fs_element.h"

namespace fs {

class File final : public FSElement, public std::enable_shared_from_this<File> {
 public:
  File(const std::shared_ptr<Directory>& parent, const std::string& name,
       const std::string& owner, unsigned int size);
  bool isFile() const;
  void setSize(unsigned int size);
  unsigned int getSize() const;
  void accept(FSVisitor& v);
  unsigned int getDiskUtil() const;
  std::string getInfo() const;
};

}  // end of namespace fs

#endif  // FILE_H
