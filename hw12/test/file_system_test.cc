#include <memory>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libfile_system.h"

namespace fs {
namespace {

class FileSystemTest : public testing::Test {
 protected:
  FileSystem& file_system_ = FileSystem::getFileSystem();
  std::shared_ptr<Directory> root_ = file_system_.getRoot();
};

TEST_F(FileSystemTest, createTreeAndTestRootSize) {
  auto system = std::make_shared<Directory>(root_, "system", "root");
  system->appendChild(std::make_shared<File>(system, "a", "root", 20));
  system->appendChild(std::make_shared<File>(system, "b", "root", 20));
  system->appendChild(std::make_shared<File>(system, "c", "root", 20));
  auto home = std::make_shared<Directory>(root_, "home", "root");
  auto pictures = std::make_shared<Directory>(home, "pictures", "user");
  pictures->appendChild(std::make_shared<File>(pictures, "e", "user", 20));
  pictures->appendChild(std::make_shared<File>(pictures, "f", "user", 20));
  home->appendChild(pictures);
  home->appendChild(std::make_shared<File>(home, "d", "user", 20));
  root_->appendChild(system);
  root_->appendChild(home);
  EXPECT_EQ(120, root_->getSize());
}

TEST_F(FileSystemTest, printAllElements) { file_system_.showAllElements(); }

}  // end of namspace unnamed
}  // end of namspace fs
