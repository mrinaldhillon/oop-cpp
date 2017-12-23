#include "lib/libfile_system.h"

int main() {
  fs::Shell shell;
  shell.startShell(fs::FileSystem::getFileSystem());
  return 0;
}
