#ifndef CHOWN_H
#define CHOWN_H

#include <iterator>
#include <regex>
#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file.h"
#include "lib/file_system.h"
#include "lib/link.h"

namespace fs {

class Chown : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "chown";
  std::string options_;

 public:
  Chown(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Chown(const Chown& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Chown& operator=(const Chown& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    std::vector<std::string> options;
    if (options_.empty()) throw std::invalid_argument("chown: missing operand");
    std::regex ws_re("\\s+");
    std::copy(
        std::sregex_token_iterator(options_.begin(), options_.end(), ws_re, -1),
        std::sregex_token_iterator(), std::back_inserter(options));

    if (options.size() != 2) {
      throw std::invalid_argument("chown: invalid input arguments");
    }

    auto target_path = options.back();
    auto owner = options.front();

    auto target_fs_element = fs_->getElement(target_path);
    if (nullptr == target_fs_element) {
      throw std::runtime_error("chown: " + target_path +
                               " : file/dir not found");
    }
    target_fs_element->setOwner(owner);
  }
};

}  // end of namespace

#endif  // CHOWN_H
