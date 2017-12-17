#include "lib/shell.h"
#include <iostream>
#include "lib/command_history.h"
#include "lib/history.h"
#include "lib/ls.h"
#include "lib/pwd.h"
#include "lib/cd.h"

namespace fs {

Shell::Shell() {}

void Shell::parseInputAndExecuteCmd(FileSystem& fs, const std::string& input) {
  std::string options;
  auto app = input.substr(0, input.find(" "));
  if (app != input) {
    options = input.substr(app.size() + 1);  //+1 forwhite space
  }
  
if (app == "pwd") {
    auto pwd = std::make_shared<Pwd>(fs);
    pwd->execute();
    cmd_history_.push(pwd);
  } else if (app == "ls") {
    auto ls = std::make_shared<Ls>(fs, options);
    ls->execute();
    cmd_history_.push(ls);
  } else if (app == "history") {
    auto history = std::make_shared<History>(cmd_history_);
    history->execute();
    cmd_history_.push(history);
  } else if (app == "cd") {
    auto cd = std::make_shared<Cd>(fs, options);
    cd->execute();
    cmd_history_.push(cd);
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
