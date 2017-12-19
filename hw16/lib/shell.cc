#include "lib/shell.h"
#include <iostream>
#include "lib/cd.h"
#include "lib/chown.h"
#include "lib/command_history.h"
#include "lib/cp.h"
#include "lib/dir.h"
#include "lib/history.h"
#include "lib/ln.h"
#include "lib/ls.h"
#include "lib/mkdir.h"
#include "lib/mv.h"
#include "lib/pwd.h"
#include "lib/redo.h"
#include "lib/rmdir.h"
#include "lib/sort.h"

namespace fs {

void Shell::parseInputAndExecuteCmd(FileSystem& fs, const std::string& input) {
  std::string options;
  auto app = input.substr(0, input.find(" "));
  if (app != input) {
    options = input.substr(app.size() + 1);  //+1 forwhite space
  }

  std::unique_ptr<Command> cmd = nullptr;
  try {
    if (app == "pwd") {
      cmd = std::make_unique<Pwd>(fs);
    } else if (app == "ls") {
      cmd = std::make_unique<Ls>(fs);
    } else if (app == "history") {
      cmd = std::make_unique<History>(cmd_history_);
    } else if (app == "cd") {
      cmd = std::make_unique<Cd>(fs, options);
    } else if (app == "dir") {
      cmd = std::make_unique<Dir>(fs, options);
    } else if (app == "mkdir") {
      cmd = std::make_unique<Mkdir>(fs, options);
    } else if (app == "rmdir") {
      cmd = std::make_unique<Rmdir>(fs, options);
    } else if (app == "ln") {
      cmd = std::make_unique<Ln>(fs, options);
    } else if (app == "mv") {
      cmd = std::make_unique<Mv>(fs, options);
    } else if (app == "cp") {
      cmd = std::make_unique<Cp>(fs, options);
    } else if (app == "chown") {
      cmd = std::make_unique<Chown>(fs, options);
    } else if (app == "redo") {
      cmd = std::make_unique<Redo>(cmd_history_);
    } else if (app == "sort") {
      cmd = std::make_unique<Sort>(fs, options);
    } else if (app == "exit") {
      exit(0);
    } else {
      std::cout << app << ": command not found..." << std::endl;
    }

    if (nullptr != cmd) cmd->execute();
    cmd_history_.push(std::move(cmd));
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
    cmd_history_.push(std::move(cmd));
  } catch (const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
    cmd_history_.push(std::move(cmd));
  }
}

void Shell::startShell(FileSystem& fs) {
  while (true) {
    std::string user_input;
    std::cout << prompt_;
    std::getline(std::cin, user_input);
    if (user_input.empty()) continue;
    parseInputAndExecuteCmd(fs, user_input);
  }
}

}  // end of namespace fs
