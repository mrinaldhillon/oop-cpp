#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <tuple>
#include <vector>
#include <memory>
#include "lib/comparator.h"
#include "lib/fs_element.h"
#include "lib/directory.h"
#include "lib/file.h"

namespace fs {

class FileSystem final {
 private:
  FileSystem();
  std::shared_ptr<Directory> root_;
  std::shared_ptr<Directory> current_;

  void showAllChildrenRecursive(
      const std::string& dir_path,
      const std::vector<std::shared_ptr<FSElement>> children) const;
  int getInsertionLocation(const Directory& parent,
                           std::shared_ptr<FSElement> child) const;

 public:
  FileSystem(const FileSystem&) = delete;
  FileSystem& operator=(const FileSystem) = delete;

  static FileSystem& getFileSystem() {
    static FileSystem instance_;
    return instance_;
  }

  void showAllElements() const;

  std::shared_ptr<Directory> getRoot() const;
  void setRoot(const std::shared_ptr<Directory>&);
  std::shared_ptr<Directory> getCurrent() const;
  void setCurrent(std::shared_ptr<Directory>);
  void addChild(Directory& parent, std::shared_ptr<FSElement> child);
  void addChild(std::shared_ptr<FSElement> child);
  const std::vector<std::shared_ptr<FSElement>> getChildren(
      const Directory& parent) const;
  const std::vector<std::shared_ptr<FSElement>> getChildren() const;
  std::shared_ptr<FSElement> getElement(const std::string& path) const;
  std::vector<std::shared_ptr<FSElement>> sort(const Directory& parent,
                                               Comparator& comp) const;
  std::tuple<int, int, int> countDirsFilesLinks(Directory&) const;
  std::tuple<int, int, int> countDirsFilesLinks() const;
  unsigned int getDiskUtil(FSElement& element) const;
  unsigned int getDiskUtil() const;
  const std::vector<std::shared_ptr<File>> searchFileTypes(
      Directory&, const std::string& extension) const;
  const std::vector<std::shared_ptr<File>> searchFileTypes(
      const std::string& extension) const;
};

}  // end of namespace fs

#endif  // FILE_SYSTEM_H
