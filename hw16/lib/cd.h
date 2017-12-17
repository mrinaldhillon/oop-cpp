#ifndef CD_H
#define CD_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Cd : public Command {
 private:
  FileSystem* fs_;

  void iterate(Directory& element) {
    std::shared_ptr<Directory> dir;
    if (dir = element.getParent().lock()) {
      iterate(*dir);
      std::cout << element.getName() << "/";
    } else {
      std::cout << element.getName();
    }
  }

 public:
  Cd(FileSystem& fs, const std::string& options)
      : Command("cd", options), fs_(&fs) {}

  void execute() {
    auto current = fs_->getCurrent();
    std::string dir_name = options_;

    if (dir_name.empty()) {  // cd
      fs_->setCurrent(fs_->getRoot());
    } else if (dir_name == "..") {  // cd ..
      if (current->getName() != "/")
        if (auto parent = current->getParent().lock()) {
          fs_->setCurrent(parent);
        }
    } else {
      for (auto child : fs_->getChildren()) {
        if (!child->isFile() && child->getName() == dir_name)
          fs_->setCurrent(std::dynamic_pointer_cast<Directory>(child));
      }
    }
  }
};

}  // end of namespace

#endif  // CD_H
