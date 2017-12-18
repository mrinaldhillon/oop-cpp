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
  const CommandHistory* history_;
  const std::string name_ = "history_";

 public:
  History(const CommandHistory& history) : history_(&history) {}
  History(const History& rhs) : history_(rhs.history_) {}
  History& operator=(const History& rhs) {
    history_ = rhs.history_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return ""; }

  void execute() {
    for (const auto& cmd : history_->getHistory()) {
      std::cout << cmd->getName();
	std::string options = cmd->getOptions();
	if (!options.empty())
		std::cout << " " << cmd->getOptions() << std::endl;
	else
		std::cout << std::endl;
    }
  }
};

}  // end of namespace

#endif  // HISTORY_H
