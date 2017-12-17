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
  const std::string name_;
  std::string options_;

 public:
  Command(const std::string& app_name, const std::string& options)
      : name_(app_name), options_(options) {}

  Command(const Command&) = default;
  Command(Command&&) = default;
  Command& operator=(const Command&) = default;
  Command& operator=(Command&&) = default;
  virtual ~Command() {};
  virtual std::string getName() { return name_; }
  virtual std::string getOptions() { return options_; }
  virtual void execute() = 0;  // throws run time error
};

}  // end of namespace fs

#endif  // COMMAND_H
