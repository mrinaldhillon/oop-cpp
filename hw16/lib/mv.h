#ifndef MV_H
#define MV_H

#include <iterator>
#include <regex>
#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file_system.h"
#include "lib/link.h"

namespace fs {

class Mv : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "mv";
  std::string options_;

 public:
  Mv(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Mv(const Mv& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Mv& operator=(const Mv& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    std::vector<std::string> options;
    if (options_.empty()) throw std::invalid_argument("mv: missing operand");
    std::regex ws_re("\\s+");
    std::copy(
        std::sregex_token_iterator(options_.begin(), options_.end(), ws_re, -1),
        std::sregex_token_iterator(), std::back_inserter(options));

    if (options.size() != 2) {
      throw std::invalid_argument("mv: invalid input arguments");
    }

    auto dst_dir_path = options.back();
    auto src_path = options.front();

    auto src_fs_element = fs_->getElement(src_path);
    if (nullptr == src_fs_element) {
      throw std::runtime_error("mv: cannot move " + src_path +
                               " : Src file/dir not found");
    }

    auto dst_fs_element = fs_->getElement(dst_dir_path);
    if (nullptr == dst_fs_element) {
      throw std::runtime_error("mv: cannot move " + dst_dir_path +
                               " : dest dir not found");
    }

    if (dst_fs_element->isFile()) {
      throw std::runtime_error("mv: cannot move " + dst_dir_path +
                               " : dest path is non directory");
    }

    auto dst_dir_element = std::dynamic_pointer_cast<Directory>(dst_fs_element);

    for (auto child : dst_dir_element->getChildren()) {
      if (child->getName() == src_fs_element->getName()) {
        dst_dir_element->rmChild(child->getName());
      }
    }

    src_fs_element->setParent(dst_dir_element);
    dst_dir_element->appendChild(src_fs_element);
  }
};

}  // end of namespace

#endif  // MV_H
