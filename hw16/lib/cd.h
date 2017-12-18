#ifndef CD_H
#define CD_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Cd : public Command {
 private:
  FileSystem* fs_;
  const std::string name_ = "cd";
  std::string options_;

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
      : fs_(&fs), options_(options) {}
  Cd(const Cd& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Cd& operator=(const Cd& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

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
        if (child->getName() == dir_name) {
          if (child->isFile())
            throw std::runtime_error("cd: " + dir_name + ": Not a directory\n");
          fs_->setCurrent(std::dynamic_pointer_cast<Directory>(child));
          return;
        }
      }
      throw std::out_of_range("cd: " + options_ + "No such file or directory\n");
    }
  }
};

}  // end of namespace

#endif  // CD_H
