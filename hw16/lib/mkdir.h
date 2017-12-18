#ifndef MKDIR_H
#define MKDIR_H

#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file_system.h"

namespace fs {

class Mkdir : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "mkdir";
  std::string options_;

 public:
  Mkdir(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Mkdir(const Mkdir& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Mkdir& operator=(const Mkdir& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    std::string dir_name = options_;
    auto current = fs_->getCurrent();
    if (dir_name.empty())
      throw std::invalid_argument("mkdir: missing operand\n");

    for (auto child : current->getChildren()) {
      if (child->getName() == dir_name)
        throw std::runtime_error("mkdir:cannot create directory " + dir_name +
                                 ": File exists\n");
    }
    current->appendChild(
        std::make_shared<Directory>(current, dir_name, current->getOwner()));
  }
};

}  // end of namespace

#endif  // MKDIR_H
