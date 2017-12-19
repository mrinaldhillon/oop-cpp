#include <memory>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libfile_system.h"

namespace fs {
namespace {
class FileSystemTest : public testing::Test {
 protected:
  static FileSystem* file_system_;
  static void SetUpTestCase() {
    file_system_ = &FileSystem::getFileSystem();
    auto root = file_system_->getRoot();
    auto system = std::make_shared<Directory>(root, "system", "root");
    auto home = std::make_shared<Directory>(root, "home", "root");
    auto pictures = std::make_shared<Directory>(home, "pictures", "user");
    auto a = std::make_shared<File>(system, "a.txt", "root", 20);
    auto b = std::make_shared<File>(system, "b.txt", "root", 20);
    auto c = std::make_shared<File>(system, "c.txt", "root", 20);
    auto d = std::make_shared<File>(home, "d.txt", "user", 20);
    auto e = std::make_shared<File>(pictures, "e.png", "root", 20);
    auto f = std::make_shared<File>(pictures, "f.png", "user", 20);
    auto x = std::make_shared<Link>(home, "x", "user", system);
    auto y = std::make_shared<Link>(pictures, "y", "user", f);

    system->appendChild(a);
    system->appendChild(b);
    system->appendChild(c);
    home->appendChild(d);
    home->appendChild(x);
    home->appendChild(pictures);
    pictures->appendChild(e);
    pictures->appendChild(f);
    pictures->appendChild(y);
    root->appendChild(system);
    root->appendChild(home);
  }
};

FileSystem* FileSystemTest::file_system_ = NULL;

TEST_F(FileSystemTest, printAllElements) { file_system_->showAllElements(); }

TEST_F(FileSystemTest, rootTreeSize) {
  auto root = file_system_->getRoot();
  EXPECT_EQ(120, root->getSize());
}

TEST_F(FileSystemTest, linkTargetSize) {
  auto root = file_system_->getRoot();
  auto children = root->getChildren();
  for (const auto child : children) {
    if (child->getName() == "x") {
      EXPECT_EQ(0, std::dynamic_pointer_cast<Link>(child)->getTargetSize());
    } else if (child->getName() == "y") {
      EXPECT_EQ(20, std::dynamic_pointer_cast<Link>(child)->getTargetSize());
    }
  }
}

TEST_F(FileSystemTest, countingVisitorTest) {
  auto root = file_system_->getRoot();
  CountingVisitor v;
  root->accept(v);
  EXPECT_EQ(6, v.getFileNum());
  EXPECT_EQ(2, v.getLinkNum());
  EXPECT_EQ(4, v.getDirNum());
}

TEST_F(FileSystemTest, sizeCountingVisitorTest) {
  auto root = file_system_->getRoot();
  SizeCountingVisitor v;
  root->accept(v);
  EXPECT_EQ(120, v.getTotalSize());
}

TEST_F(FileSystemTest, fileSearchVisitorForTextFiles) {
  auto root = file_system_->getRoot();
  FileSearchVisitor v(".txt");
  root->accept(v);
  EXPECT_EQ(4, v.getFoundFiles().size());
}

TEST_F(FileSystemTest, fileSearchVisitorForPNGFiles) {
  auto root = file_system_->getRoot();
  FileSearchVisitor v(".png");
  root->accept(v);
  EXPECT_EQ(2, v.getFoundFiles().size());
}

TEST_F(FileSystemTest, compareSortedWithReverseSorted) {
  auto root = file_system_->getRoot();
  auto sorted = root->getChildren(); // children sorted by default
  ReverseAlphabeticalComparator reverse_comp;
  auto reverse_sorted = file_system_->sort(*root, reverse_comp);
  EXPECT_THAT(sorted,
              ::testing::WhenSortedBy(reverse_comp, reverse_sorted));
}

}  // end of namspace unnamed
}  // end of namspace fs
