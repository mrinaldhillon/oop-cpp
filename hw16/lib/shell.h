#ifndef SHELL_H
#define SHELL_H

#include <string>
#include "lib/command.h"
#include "lib/command_history.h"
#include "lib/file_system.h"

namespace fs {

class Shell final {
 private:
  std::string prompt_ = "> ";
  CommandHistory cmd_history_;

 protected:
  void executeCmd(Command& cmd,
                  const std::vector<const std::string>& cmd_tokens);

 public:
  // maintain a history object per shell.
  Shell();

  void parseInputAndExecuteCmd(FileSystem& fs, const std::string& input);
  void startShell(FileSystem& fs);
};

}  // end of namespace fs

#endif  // SHELL_H
