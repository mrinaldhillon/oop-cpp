#include "lib/file_system.h"
#include <cassert>
#include <iostream>
#include <vector>

namespace fs {

FileSystem::FileSystem()
    : root_(std::make_shared<Directory>(nullptr, "/", "root")),
      current_(root_){};

void FileSystem::showAllChildrenRecursive(
    const std::string& dir_path,
    const std::vector<std::shared_ptr<FSElement>> children) const {
  for (auto child : children) {
    std::string file_path = dir_path + "/" + child->getName();
    std::cout << file_path << std::endl;
    if (false == child->isFile()) {
      showAllChildrenRecursive(
          file_path,
          std::dynamic_pointer_cast<Directory>(child)->getChildren());
    }
  }
}

void FileSystem::showAllElements() const {
  showAllChildrenRecursive("", root_->getChildren());
}

std::shared_ptr<Directory> FileSystem::getRoot() const { return root_; }

void FileSystem::setRoot(const std::shared_ptr<Directory>& root) {
  root_ = root;  // TBD: show the root pointer be reset
}

std::shared_ptr<Directory> FileSystem::getCurrent() const { return current_; }

void FileSystem::setCurrent(std::shared_ptr<Directory> current) {
  current_ = current;
}

void FileSystem::addChild(Directory& parent, std::shared_ptr<FSElement> child) {
  // TODO: use sort
  parent.addChild(child, parent.getChildren().size() - 1);
}

void FileSystem::addChild(std::shared_ptr<FSElement> child) {
  // TODO: use sort
  current_->addChild(child, current_->getChildren().size() - 1);
}

const std::vector<std::shared_ptr<FSElement>> FileSystem::getChildren(
    const Directory& parent) const {
  // TBD: Not sure why this is useful
  return parent.getChildren();
}

const std::vector<std::shared_ptr<FSElement>> FileSystem::getChildren() const {
  return current_->getChildren();
}

}  // end of namespace fs
