#ifndef FILE_SEARCH_VISITOR_H
#define FILE_SEARCH_VISITOR_H

#include "lib/directory.h"
#include "lib/file.h"
#include "lib/fs_visitor.h"
#include "lib/link.h"

namespace fs {

class FileSearchVisitor : public FSVisitor {
 private:
  std::vector<std::shared_ptr<File>> found_files_;
  std::string extension_;

 public:
  FileSearchVisitor(const std::string& extension)
      : found_files_{}, extension_(extension) {}
  void visit(const std::shared_ptr<Link>&) {}
  void visit(const std::shared_ptr<Directory>&) {}
  void visit(const std::shared_ptr<File>& file) {
    auto file_name = file->getName();
    if (file_name.size() >= extension_.size() &&
        file_name.compare(file_name.size() - extension_.size(),
                          extension_.size(), extension_) == 0)
      found_files_.push_back(file);
  }
  const std::vector<std::shared_ptr<File>> getFoundFiles() {
    return found_files_;
  }
};

}  // end of namespace fs

#endif  // FILE_SEARCH_VISITOR_H
