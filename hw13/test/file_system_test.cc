#include <memory>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libfile_system.h"

namespace fs {
namespace {
class FileSystemTest : public testing::Test {
 protected:
  FileSystem& file_system__ = FileSystem::getFileSystem();
  std::shared_ptr<Directory> root_ = file_system__.getRoot();
  std::shared_ptr<Directory> system_ = std::make_shared<Directory>(root_, "system_", "root");
   std::shared_ptr<Directory> home_ = std::make_shared<Directory>(root_, "home_", "root");
   std::shared_ptr<Directory> picture_ = std::make_shared<Directory>(home_, "picture_", "user");
  std::shared_ptr<File> f_ = std::make_shared<File>(picture_, "f", "user", 20);
  std::shared_ptr<Link> y_ = std::make_shared<Link>(picture_, "y", "user", f_);
  std::shared_ptr<Link> x_ = std::make_shared<Link>(home_, "x", "user", system_);
};

TEST_F(FileSystemTest, createTreeAndTestRootSize) {
  system_->appendChild(std::make_shared<File>(system_, "a", "root", 20));
  system_->appendChild(std::make_shared<File>(system_, "b", "root", 20));
  system_->appendChild(std::make_shared<File>(system_, "c", "root", 20));

  picture_->appendChild(std::make_shared<File>(picture_, "e", "user", 20));
  picture_->appendChild(f_);
  picture_->appendChild(y_);
  home_->appendChild(picture_);
  home_->appendChild(x_);
  home_->appendChild(std::make_shared<File>(home_, "d", "user", 20));

  root_->appendChild(system_);
  root_->appendChild(home_);

  EXPECT_EQ(120, root_->getSize());

}

TEST_F(FileSystemTest, linkTargetSize) {
  EXPECT_EQ(0, x_->getTargetSize());
  EXPECT_EQ(20, y_->getTargetSize());
}

TEST_F(FileSystemTest, printAllElements) { file_system__.showAllElements(); }

}  // end of namspace unnamed
}  // end of namspace fs
