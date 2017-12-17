#ifndef COMMAND_HISTORY_H
#define COMMAND_HISTORY_H

#include <deque>
#include <memory>
#include "lib/command.h"

namespace fs {

// TODO shared_ptr is not requires, instead copy by value
class CommandHistory {
 private:
  std::deque<std::shared_ptr<Command>> history_;

 public:
  void push(std::shared_ptr<Command> cmd) { history_.push_front(cmd); }

  std::shared_ptr<Command> pop() {
    auto cmd = history_.front();
    history_.pop_front();
    return cmd;
  }

  const std::deque<std::shared_ptr<Command>> getHistory() { return history_; }
};

}  // end of namespace fs
#endif  // COMMAND_HISTORY_H
