#ifndef DU_H
#define DU_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Du : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "du";
  std::string options_;

 public:
  Du(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Du(const Du& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Du& operator=(const Du& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    if (options_.empty()) {
      std::cout << fs_->getDiskUtil() << std::endl;
      return;
    }

    auto fs_element = fs_->getElement(options_);
    if (nullptr == fs_element) {
      throw std::range_error("du: " + options_ + " No such file or directory");
    }

    std::cout << fs_->getDiskUtil(*fs_element) << std::endl;
  }
};

}  // end of namespace

#endif  // DU_H
