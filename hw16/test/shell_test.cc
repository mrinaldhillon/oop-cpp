#include <memory>
#include <sstream>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libfile_system.h"

namespace fs {
namespace {

class ShellTest : public testing::Test {
 protected:
  static FileSystem* fs_;
  static Shell shell_;
  static void SetUpTestCase() {
    fs_ = &FileSystem::getFileSystem();
    auto root = fs_->getRoot();
    auto system = std::make_shared<Directory>(root, "system", "root");
    auto home = std::make_shared<Directory>(root, "home", "root");
    auto pictures = std::make_shared<Directory>(home, "pictures", "user");
    auto a = std::make_shared<File>(system, "a.txt", "root", 10);
    auto b = std::make_shared<File>(system, "b.txt", "root", 10);
    auto c = std::make_shared<File>(system, "c.txt", "root", 10);
    auto d = std::make_shared<File>(home, "d.txt", "user", 10);
    auto e = std::make_shared<File>(pictures, "e.png", "user", 10);
    auto f = std::make_shared<File>(pictures, "f.png", "user", 10);
    auto x = std::make_shared<Link>(home, "x", "user", system);
    auto y = std::make_shared<Link>(pictures, "y", "user", f);

    fs_->addChild(*system, a);
    fs_->addChild(*system, b);
    fs_->addChild(*system, c);
    fs_->addChild(*home, d);
    fs_->addChild(*home, x);
    fs_->addChild(*home, pictures);
    fs_->addChild(*pictures, e);
    fs_->addChild(*pictures, f);
    fs_->addChild(*pictures, y);
    fs_->addChild(*root, system);
    fs_->addChild(*root, home);
  }
};

FileSystem* ShellTest::fs_ = NULL;
Shell ShellTest::shell_;

std::string getStdout(Shell& shell, FileSystem& fs, const std::string& input) {
  std::stringstream buffer;
  std::streambuf* sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  shell.parseInputAndExecuteCmd(fs, input);
  std::string output = buffer.str();
  std::cout.rdbuf(sbuf);
  return output;
}

void suppressStdout(Shell& shell, FileSystem& fs, const std::string& input) {
  std::stringstream buffer;
  std::streambuf* sbuf = std::cout.rdbuf();
  std::cout.rdbuf(nullptr);
  shell.parseInputAndExecuteCmd(fs, input);
  std::cout.rdbuf(sbuf);
}

TEST_F(ShellTest, visitors) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cd");
  EXPECT_EQ(getStdout(shell_, *fs_, "count"), "Dirs :4, Files :6, Links :2\n");
  EXPECT_EQ(getStdout(shell_, *fs_, "search .txt"),
            "d.txt\na.txt\nb.txt\nc.txt\n");
  EXPECT_EQ(getStdout(shell_, *fs_, "du"), "60\n");
}

TEST_F(ShellTest, historyCmd) {
  Shell shell;
  suppressStdout(shell, *fs_, "pwd");
  suppressStdout(shell, *fs_, "ls");
  EXPECT_EQ(getStdout(shell, *fs_, "history"), "ls\npwd\n");
}

TEST_F(ShellTest, lsCmd) {
  Shell shell;
  EXPECT_EQ(getStdout(shell, *fs_, "ls /"), "home\nsystem\n");
}

TEST_F(ShellTest, cdCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cd");
  shell.parseInputAndExecuteCmd(*fs_, "cd home");
  EXPECT_EQ(fs_->getCurrent()->getName(), "home");
  shell.parseInputAndExecuteCmd(*fs_, "cd ./pictures");
  EXPECT_EQ(fs_->getCurrent()->getName(), "pictures");
  shell.parseInputAndExecuteCmd(*fs_, "cd ..");
  EXPECT_EQ(fs_->getCurrent()->getName(), "home");
  shell.parseInputAndExecuteCmd(*fs_, "cd /system/../home/pictures/./");
  EXPECT_EQ(fs_->getCurrent()->getName(), "pictures");
  EXPECT_EQ(getStdout(shell, *fs_, "cd blah"), "cd: blah : dir not found\n");
  EXPECT_EQ(getStdout(shell, *fs_, "cd /home/pictures/e.png"),
            "cd: /home/pictures/e.png : target is non directory\n");
}

TEST_F(ShellTest, pwdCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cd /home/pictures");
  EXPECT_EQ(getStdout(shell, *fs_, "pwd"), "/home/pictures/\n");
}

TEST_F(ShellTest, dirCmd) {
  Shell shell;
  auto dtxt = fs_->getElement("/home/d.txt");
  std::time_t mod_time = dtxt->getModTime();
  std::ostringstream oss;
  oss << "file\tuser\t10\t" << std::asctime(std::localtime(&mod_time))
      << "\td.txt\n";
  EXPECT_EQ(getStdout(shell, *fs_, "dir /home/d.txt"), oss.str());
}

TEST_F(ShellTest, mkdirCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cd");
  shell.parseInputAndExecuteCmd(*fs_, "mkdir tmp");
  shell.parseInputAndExecuteCmd(*fs_, "cd tmp");
  EXPECT_EQ(fs_->getCurrent()->getName(), "tmp");
  EXPECT_EQ(getStdout(shell, *fs_, "mkdir"), "mkdir: missing operand\n");
  shell.parseInputAndExecuteCmd(*fs_, "cd");
  EXPECT_EQ(getStdout(shell, *fs_, "mkdir tmp"),
            "mkdir: cannot create directory tmp : File/dir exists\n");
}

TEST_F(ShellTest, rmdirCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cd");
  shell.parseInputAndExecuteCmd(*fs_, "rmdir tmp");
  EXPECT_EQ(getStdout(shell, *fs_, "rmdir tmp"),
            "rmdir: failed to remove tmp : No such file or directory\n");
  EXPECT_EQ(getStdout(shell, *fs_, "rmdir"), "rmdir: missing operand\n");
  shell.parseInputAndExecuteCmd(*fs_, "cd home");
  EXPECT_EQ(getStdout(shell, *fs_, "rmdir d.txt"),
            "rmdir: failed to remove d.txt : Not a directory\n");
}

TEST_F(ShellTest, lnCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cd");
  shell.parseInputAndExecuteCmd(*fs_, "mkdir tmp");
  shell.parseInputAndExecuteCmd(*fs_, "cd /tmp");
  shell.parseInputAndExecuteCmd(*fs_, "ln /home/pictures/e.png e");
  EXPECT_EQ(fs_->getElement("/tmp/e")->getName(), "e");
  EXPECT_EQ(getStdout(shell, *fs_, "ln"), "ln: missing operand\n");
  EXPECT_EQ(getStdout(shell, *fs_, "ln blah"), "ln: invalid input arguments\n");
  EXPECT_EQ(getStdout(shell, *fs_, "ln /home/uv w"),
            "ln: cannot create link w : Target /home/uv not found\n");
  EXPECT_EQ(getStdout(shell, *fs_, "ln /home/pictures/e.png e"),
            "ln: cannot create link e : File/Dir exists\n");
}

TEST_F(ShellTest, mvCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "mv /home/pictures/e.png /tmp");
  EXPECT_EQ(fs_->getElement("/tmp/e.png")->getName(), "e.png");
  EXPECT_EQ(getStdout(shell, *fs_, "mv"), "mv: missing operand\n");
  EXPECT_EQ(getStdout(shell, *fs_, "mv blah"), "mv: invalid input arguments\n");
  EXPECT_EQ(getStdout(shell, *fs_, "mv /home/d.txt /bla"),
            "mv: cannot move /bla : dest dir not found\n");
  EXPECT_EQ(getStdout(shell, *fs_, "mv /home/d.txt /tmp/e.png"),
            "mv: cannot move /tmp/e.png : dest path is non directory\n");
  EXPECT_EQ(getStdout(shell, *fs_, "mv bla /tmp"),
            "mv: cannot move bla : Src file/dir not found\n");
  shell.parseInputAndExecuteCmd(*fs_, "mv /tmp/e.png /home/pictures");
}

TEST_F(ShellTest, cpCmd) {
  Shell shell;
  shell.parseInputAndExecuteCmd(*fs_, "cp /home/pictures/e.png /tmp");
  EXPECT_EQ(fs_->getElement("/tmp/e.png")->getName(), "e.png");
  shell.parseInputAndExecuteCmd(*fs_, "cp /home/pictures /tmp");
  EXPECT_EQ(fs_->getElement("/tmp/pictures/e.png")->getName(), "e.png");
  EXPECT_EQ(getStdout(shell, *fs_, "cp"), "cp: missing operand\n");
  EXPECT_EQ(getStdout(shell, *fs_, "cp blah"), "cp: invalid input arguments\n");
  EXPECT_EQ(getStdout(shell, *fs_, "cp /home/d.txt /bla"),
            "cp: cannot copy to /bla : dest dir not found\n");
  EXPECT_EQ(getStdout(shell, *fs_, "cp /home/d.txt /tmp/e.png"),
            "cp: cannot copy to /tmp/e.png : dest path is non directory\n");
  EXPECT_EQ(getStdout(shell, *fs_, "cp bla /tmp"),
            "cp: cannot copy bla : Src file/dir not found\n");
}

TEST_F(ShellTest, chownCmd) {
  //  Shell shell;
  shell_.parseInputAndExecuteCmd(*fs_, "chown newuser /tmp");
  EXPECT_EQ(fs_->getElement("/tmp")->getOwner(), "newuser");
  EXPECT_EQ(getStdout(shell_, *fs_, "chown"), "chown: missing operand\n");
  EXPECT_EQ(getStdout(shell_, *fs_, "chown /tmp"),
            "chown: invalid input arguments\n");
  EXPECT_EQ(getStdout(shell_, *fs_, "chown user /bla"),
            "chown: /bla : file/dir not found\n");
}

TEST_F(ShellTest, redoCmd) {
  //  Shell shell;
  EXPECT_EQ(getStdout(shell_, *fs_, "redo"),
            "chown: /bla : file/dir not found\n");
}

TEST_F(ShellTest, sortCmd) {
  Shell shell;

  shell.parseInputAndExecuteCmd(*fs_, "cd");
  EXPECT_EQ(getStdout(shell_, *fs_, "sort"), "home\nsystem\ntmp\n");
  EXPECT_EQ(getStdout(shell_, *fs_, "sort reverse"), "tmp\nsystem\nhome\n");
  sleep(1);
  shell.parseInputAndExecuteCmd(*fs_, "cp /home /system/");
  EXPECT_EQ(getStdout(shell_, *fs_, "sort time"), "home\ntmp\nsystem\n");
  shell.parseInputAndExecuteCmd(*fs_, "cd /system");
  shell.parseInputAndExecuteCmd(*fs_, "rmdir home");
}

}  // end of namespace unnamed
}  // end of namespace fs
