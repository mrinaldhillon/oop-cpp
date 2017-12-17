#ifndef COMMAND_H
#define COMMAND_H

#include <deque>
#include <iterator>
#include <regex>
#include <string>
#include "lib/file_system.h"

namespace fs {

class Command {
 protected:
  const FileSystem* fs_;
  const std::string name_;
  std::string options_;
  std::deque<std::string> options_tokens_{};

 public:
  Command(const FileSystem& fs, const std::string& options,
          const std::string& app_name)
      : fs_(&fs), name_(app_name), options_(options) {
    if (options.empty()) return;
    std::regex ws_re("\\s+");
    std::copy(
        std::sregex_token_iterator(options.begin(), options.end(), ws_re, -1),
        std::sregex_token_iterator(), std::back_inserter(options_tokens_));
  }

  Command(const Command&) = default;
  Command(Command&&) = default;
  Command& operator=(const Command&) = default;
  Command& operator=(Command&&) = default;
  virtual ~Command() = default;
  virtual std::string getName() { return name_; }
  virtual std::string getOptions() { return options_; }
  virtual void execute() = 0;  // throws run time error
};

}  // end of namespace fs

#endif  // COMMAND_H
