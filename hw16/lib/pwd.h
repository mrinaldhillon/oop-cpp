#ifndef PWD_H
#define PWD_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Pwd : public Command {
 private:
  const FileSystem* fs_;
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
  Pwd(const FileSystem& fs) : Command("pwd", ""), fs_(&fs) {}

  void execute() {
    auto current = fs_->getCurrent();
    iterate(*current);
  }
};

}  // end of namespace

#endif  // PWD_H
