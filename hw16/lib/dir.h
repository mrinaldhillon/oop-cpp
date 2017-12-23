#ifndef DIR_H
#define DIR_H

#include <iostream>
#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file_system.h"

namespace fs {

class Dir : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "dir";
  std::string options_;

  void print_info(FSElement& element) {
    if (element.isFile()) {
      std::cout << element.getInfo() << std::endl;
      return;
    }

      std::cout << element.getInfo() << std::endl;
    for (const auto child : dynamic_cast<Directory&>(element).getChildren()) {
      std::cout << child->getInfo() << std::endl;
    }
  }

 public:
  Dir(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Dir(const Dir& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Dir& operator=(const Dir& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    if (options_.empty()) {
      print_info(*fs_->getCurrent());
      return;
    }

    auto target_fs_element = fs_->getElement(options_);
    if (nullptr == target_fs_element) {
      throw std::runtime_error("dir: " + options_ + ": file/dir not found");
    }

    print_info(*target_fs_element);
  }
};

}  // end of namespace

#endif  // DIR_H
