#ifndef COMMAND_H
#define COMMAND_H

#include <deque>
#include <iterator>
//#include <regex>
#include <string>
#include "lib/file_system.h"

namespace fs {

class Command {
 public:
  /*  Command(const Command&) = default;
    Command(Command&&) = default;
    Command& operator=(const Command&) = default;
    Command& operator=(Command&&) = default;*/
//Command& operator=(const Command&) = delete;
  //Command(const Command&) = delete;

  virtual ~Command() {};
  virtual std::string getName() const = 0;
  virtual std::string getOptions() const = 0;
  virtual void execute() = 0;  // throws run time error
};

}  // end of namespace fs

#endif  // COMMAND_H
