#ifndef PWD_H
#define PWD_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Pwd : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "pwd";

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
  Pwd(const FileSystem& fs) : fs_(&fs) {}
  Pwd(const Pwd& rhs) : fs_(rhs.fs_) {}
  Pwd& operator=(const Pwd& rhs) {
    fs_ = rhs.fs_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return ""; }

  void execute() {
    auto current = fs_->getCurrent();
    iterate(*current);
    std::cout << std::endl;
  }
};

}  // end of namespace

#endif  // PWD_H
