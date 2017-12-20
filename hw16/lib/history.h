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
  const std::string name_ = "history";

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
    auto& history = history_->getHistory();
    if (history.empty()) {
      std::cout << "history is empty" << std::endl;
      return;
    }

    for (const auto& cmd : history_->getHistory()) {
      std::cout << cmd->getName();
      auto options = cmd->getOptions();
      if (!options.empty())
        std::cout << " " << options << std::endl;
      else
        std::cout << std::endl;
    }
  }
};

}  // end of namespace

#endif  // HISTORY_H
