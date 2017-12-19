#ifndef RMDIR_H
#define RMDIR_H

#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file_system.h"

namespace fs {

class Rmdir : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "rmdir";
  std::string options_;

 public:
  Rmdir(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Rmdir(const Rmdir& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Rmdir& operator=(const Rmdir& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    std::string dir_name = options_;
    auto current = fs_->getCurrent();
    if (dir_name.empty()) throw std::invalid_argument("rmdir: missing operand");

    for (auto child : current->getChildren()) {
      if (child->getName() == dir_name) {
        if (!child->isFile()) {
          current->rmChild(dir_name);
        } else {
          throw std::runtime_error("rmdir: failed to remove" + dir_name +
                                   ": Not a directory");
        }
        return;
      }
    }
    throw std::range_error("rmdir: failed to remove" + dir_name +
                           ": No such file or directory");
  }
};

}  // end of namespace

#endif  // RMDIR_H
