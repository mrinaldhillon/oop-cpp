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

  void dir_children(Directory& parent) {
    for (const auto child : parent.getChildren()) {
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
    std::string element_name = options_;
    auto current = fs_->getCurrent();
    if (element_name.empty()) {  // dir
      dir_children(*current);
      return;
    }

    if (element_name == "..") {  // dir ..
      if (current->getName() == "/") {
        dir_children(*fs_->getRoot());
      } else if (auto parent = current->getParent().lock()) {
        dir_children(*parent);
      }  // Should throw an error here, parent probably while child is still
      // around this is a design issue due to weak pointers as parents to
      // break circular ref of shared pointers between parent and children
      return;
    }
    for (auto child : fs_->getChildren()) {
      if (child->getName() == element_name) {
        if (!child->isFile()) {
          dir_children(*std::dynamic_pointer_cast<Directory>(child));
        } else {
          std::cout << child->getInfo() << std::endl;
        }
      }
      return;
    }
    throw std::out_of_range("cd: " + options_ + "No such file or directory\n");
  }
};

}  // end of namespace

#endif  // DIR_H
