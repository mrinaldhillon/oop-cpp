#ifndef PWD_H
#define PWD_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Pwd : public Command {
 private:
  const FileSystem* fs_;

 public:
  Pwd(const FileSystem& fs) : fs_(&fs) {}

  void execute() {
    auto children = fs_->getChildren();
    for (const auto child : children) {
      std::cout << child->getName() << std::endl;
    }
  }
};

}  // end of namespace

#endif  // PWD_H
