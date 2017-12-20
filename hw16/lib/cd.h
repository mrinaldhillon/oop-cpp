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

    if (options_.empty()) {  // cd
      fs_->setCurrent(fs_->getRoot());
      return;
    }

    auto target_dir = fs_->getElement(options_);
    if (nullptr == target_dir) {
      throw std::range_error("cd: " + options_ + " : dir not found");
    }

    if (target_dir->isFile()) {
      throw std::runtime_error("cd: " + options_ + " : target is non directory");
    }

    fs_->setCurrent(std::dynamic_pointer_cast<Directory>(target_dir));
  }
};

}  // end of namespace

#endif  // CD_H
