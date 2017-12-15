#include "lib/file_system.h"
#include <cassert>
#include <iostream>
#include <vector>

namespace fs {

FileSystem::FileSystem()
    : root_(std::make_shared<Directory>(nullptr, "/", "root")){};

void FileSystem::showAllChildrenRecursive(
    const std::string& dir_path,
    const std::vector<std::shared_ptr<FSElement>> children) const {
  for (auto child : children) {
    std::string file_path = dir_path + "/" + child->getName();
    std::cout << file_path << std::endl;
    if (false == child->isFile()) {
      showAllChildrenRecursive(file_path, std::dynamic_pointer_cast<Directory>(child)->getChildren());
    }
  }
}

std::shared_ptr<Directory> FileSystem::getRoot() const { return root_; }

void FileSystem::showAllElements() const {
  showAllChildrenRecursive("", root_->getChildren());
}
}  // end of namespace fs
