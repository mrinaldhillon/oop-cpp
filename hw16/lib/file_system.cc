#include "lib/file_system.h"
#include <cassert>
#include <experimental/filesystem>
#include <iostream>
#include <vector>

namespace std_exp_fs = std::experimental::filesystem;

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

// TODO: dirty code
std::shared_ptr<FSElement> FileSystem::getElement(
    const std::string& path) const {
  auto tmp = path;
  if (tmp.back() == '/' && tmp.size() > 1)
    tmp.pop_back();  // TODO: difficult to handle trailing /

  std_exp_fs::path fs_path = tmp;
  std::shared_ptr<FSElement> current;
  std::shared_ptr<Directory> prev;

  if (fs_path.is_absolute())
    prev = root_;
  else
    prev = current_;

  for (auto& path_element : fs_path) {
    if (prev == nullptr) assert("Internal error");
    current = nullptr;
    if (path_element == ".") {
      current = prev;  // do nothing fs_element is current_dir
    } else if (path_element == "..") {
      if (prev->getName() != "/") {
        current = prev->getParent().lock();
      } else
        current = prev;
    } else if (path_element == "/") {
      current = root_;
    } else {
      for (auto child : prev->getChildren()) {
        if (child->getName() == path_element) {
          current = child;
          break;
        }
      }
    }
    if (nullptr == current) break;
    if (!current->isFile()) {
      prev = std::dynamic_pointer_cast<Directory>(current);
    } else
      prev = nullptr;
  }
  return current;
}

}  // end of namespace fs
