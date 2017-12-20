#ifndef LN_H
#define LN_H

#include <iterator>
#include <regex>
#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file_system.h"
#include "lib/link.h"

namespace fs {

class Ln : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "ln";
  std::string options_;

 public:
  Ln(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Ln(const Ln& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Ln& operator=(const Ln& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    std::vector<std::string> options;
    if (options_.empty()) throw std::invalid_argument("ln: missing operand");
    std::regex ws_re("\\s+");
    std::copy(
        std::sregex_token_iterator(options_.begin(), options_.end(), ws_re, -1),
        std::sregex_token_iterator(), std::back_inserter(options));

    if (options.size() != 2) {
      throw std::invalid_argument("ln: invalid input arguments");
    }

    auto link_name = options.back();
    auto target_path = options.front();

    std::shared_ptr<FSElement> target_fs_element = fs_->getElement(target_path);
    if (nullptr == target_fs_element) {
      throw std::runtime_error("ln: cannot create link " + link_name +
                               " : Target " + target_path + " not found");
    }

    if (nullptr != fs_->getElement(link_name)) {
      throw std::runtime_error("ln: cannot create link " + link_name +
                               " : File/Dir exists");
    }

    auto current = fs_->getCurrent();
    auto link = std::make_shared<Link>(current, link_name, current->getOwner(),
                                       target_fs_element);
    current->appendChild(link);
  }
};

}  // end of namespace

#endif  // LN_H
