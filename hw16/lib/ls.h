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
  // std::deque<std::string> options_tokens_{};
 public:
  Ls(const FileSystem& fs) : fs_(&fs) {}
  Ls(const Ls& ls) : fs_(ls.fs_) {}
  Ls& operator=(const Ls& ls) {
    fs_ = ls.fs_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return ""; }

  void execute() {
    /*    if (options.empty()) return;
        std::regex ws_re("\\s+");
        std::copy(
            std::sregex_token_iterator(options.begin(), options.end(), ws_re,
       -1),
            std::sregex_token_iterator(), std::back_inserter(options_tokens_));
    */
    for (const auto child : fs_->getChildren()) {
      std::cout << child->getName() << std::endl;
    }
  }
};

}  // end of namespace

#endif  // LS_H
