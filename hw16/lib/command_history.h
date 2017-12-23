#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

#include <deque>
#include <memory>
#include <vector>
#include "lib/command.h"

namespace fs {

class CommandHistory {
 private:
  std::deque<std::unique_ptr<Command>> history_{};

 public:
  CommandHistory() = default;
  CommandHistory(const CommandHistory&) = delete;
  CommandHistory& operator=(const CommandHistory&) = delete;

  void push(std::unique_ptr<Command> cmd) {
    history_.push_front(std::move(cmd));
  }

  std::unique_ptr<Command> pop() {
    auto cmd = std::move(history_.front());
    history_.pop_front();
    return cmd;
  }

  const std::deque<std::unique_ptr<Command>>& getHistory() const {
    return history_;
  }
};

}  // end of namespace fs
#endif  // COMMAND_HISTORY_H
