#ifndef LS_H
#define LS_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Ls : public Command {
 public:
  Ls(const FileSystem& fs, const std::string& options)
      : Command(fs, "ls", options) {}

  void execute() {
    for (const auto child : fs_->getChildren()) {
      std::cout << child->getName() << std::endl;
    }
  }
};

}  // end of namespace

#endif  // LS_H
