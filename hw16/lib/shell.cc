#include "lib/shell.h"
#include <iostream>
#include "lib/ls.h"

namespace fs {

Shell::Shell() {}

void Shell::parseInputAndExecuteCmd(FileSystem& fs, const std::string& input) {
  std::string options;
  auto app = input.substr(0, input.find(" "));
  if (app != input) {
    options = input.substr(app.size() + 1);  //+1 forwhite space
  }
  if (app == "ls") {
    Ls ls(fs, options);
    ls.execute();
    // push command to history
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
