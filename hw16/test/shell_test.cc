#include <memory>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libfile_system.h"

namespace fs {
namespace {

class ShellTest : public testing::Test {
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

FileSystem* ShellTest::file_system_ = NULL;

TEST_F(ShellTest, historyCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*file_system_, "pwd");
  shell.parseInputAndExecuteCmd(*file_system_, "ls");
  shell.parseInputAndExecuteCmd(*file_system_, "history");
}

TEST_F(ShellTest, lsCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*file_system_, "ls ");
}

TEST_F(ShellTest, pwdCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*file_system_, "pwd");
}

TEST_F(ShellTest, cdCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*file_system_, "cd home");
  EXPECT_EQ(file_system_->getCurrent()->getName(), "home");
  shell.parseInputAndExecuteCmd(*file_system_, "cd pictures");
  EXPECT_EQ(file_system_->getCurrent()->getName(), "pictures");
  shell.parseInputAndExecuteCmd(*file_system_, "cd ..");
  EXPECT_EQ(file_system_->getCurrent()->getName(), "home");
  shell.parseInputAndExecuteCmd(*file_system_, "cd");
  EXPECT_EQ(file_system_->getCurrent()->getName(), "/");
}

}  // end of namespace unnamed
}  // end of namespace fs
