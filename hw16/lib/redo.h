#ifndef REDO_H
#define REDO_H

#include <iostream>
#include <memory>
#include "lib/command.h"
#include "lib/command_history.h"

namespace fs {

class Redo : public Command {
 private:
  const CommandHistory* history_;
  const std::string name_ = "redo";

 public:
  Redo(const CommandHistory& history) : history_(&history) {}
  Redo(const Redo& rhs) : history_(rhs.history_) {}
  Redo& operator=(const Redo& rhs) {
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

    Command& cmd = *history.front();
    cmd.execute();
  }
};

}  // end of namespace

#endif  // REDO_H
