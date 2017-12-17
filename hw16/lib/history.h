#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <memory>
#include "lib/command.h"
#include "lib/command_history.h"
#include "lib/file_system.h"

namespace fs {

class History : public Command {
 private:
  CommandHistory history_;

 public:
  History(const CommandHistory& history)
      : Command("history", ""), history_(history) {}

  void execute() {
    for (const auto cmd : history_.getHistory()) {
      std::cout << cmd->getName() << " " << cmd->getOptions() << std::endl;
    }
  }
};

}  // end of namespace

#endif  // HISTORY_H
