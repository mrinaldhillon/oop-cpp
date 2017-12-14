#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <memory>
#include "lib/directory.h"
#include "lib/fs_element.h"

namespace fs {

class FileSystem final {
 private:
  FileSystem();
  std::shared_ptr<Directory> root_;
  void showAllChildrenRecursive(
      const std::string& dir_path,
      const std::vector<std::shared_ptr<FSElement>> children) const;

 public:
  FileSystem(const FileSystem&) = delete;
  FileSystem& operator=(const FileSystem) = delete;

  static FileSystem& getFileSystem() {
    static FileSystem instance_;
    return instance_;
  }

  std::shared_ptr<Directory> getRoot() const;
  void showAllElements() const;
};

}  // end of namespace fs

#endif  // FILE_SYSTEM_H
