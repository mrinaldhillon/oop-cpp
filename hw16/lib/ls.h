#ifndef LS_H
#define LS_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Ls : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "ls";
  std::string options_;

 public:
  Ls(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Ls(const Ls& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Ls& operator=(const Ls& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void print(Directory& dir) {
    for (const auto child : dir.getChildren()) {
      std::cout << child->getName() << std::endl;
    }
  }

  void execute() {
    if (options_.empty()) {
      print(*fs_->getCurrent());
      return;
    }

    auto target_fs_element = fs_->getElement(options_);
    if (nullptr == target_fs_element) {
      throw std::runtime_error("ls: " + options_ + ": dir not found");
    }

    if (target_fs_element->isFile()) {
      throw std::runtime_error("ls: " + options_ +
                               ": does not support file types");
    }
    print(dynamic_cast<Directory&>(*target_fs_element));
  }
};

}  // end of namespace

#endif  // LS_H
