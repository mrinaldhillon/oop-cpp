#include "lib/shell.h"
#include <iostream>
#include "lib/cd.h"
#include "lib/command_history.h"
#include "lib/history.h"
#include "lib/ls.h"
#include "lib/pwd.h"
#include "lib/dir.h"
#include "lib/mkdir.h"

namespace fs {

void Shell::parseInputAndExecuteCmd(FileSystem& fs, const std::string& input) {
  std::string options;
  auto app = input.substr(0, input.find(" "));
  if (app != input) {
    options = input.substr(app.size() + 1);  //+1 forwhite space
  }

  if (app == "pwd") {
    auto pwd = std::make_unique<Pwd>(fs);
    pwd->execute();
    cmd_history_.push(std::move(pwd));
  } else if (app == "ls") {
    auto ls = std::make_unique<Ls>(fs);
    ls->execute();
    cmd_history_.push(std::move(ls));
  } else if (app == "history") {
    auto history = std::make_unique<History>(cmd_history_);
    history->execute();
    cmd_history_.push(std::move(history));
  } else if (app == "cd") {
    auto cd = std::make_unique<Cd>(fs, options);
    cd->execute();
    cmd_history_.push(std::move(cd));
  } else if (app == "dir") {
    auto dir = std::make_unique<Dir>(fs, options);
    dir->execute();
    cmd_history_.push(std::move(dir));
  } else if (app == "mkdir") {
    auto mkdir = std::make_unique<Mkdir>(fs, options);
    mkdir->execute();
    cmd_history_.push(std::move(mkdir));
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
