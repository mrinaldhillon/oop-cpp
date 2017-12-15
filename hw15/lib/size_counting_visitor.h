#ifndef SIZE_COUNTING_VISITOR_H
#define SIZE_COUNTING_VISITOR_H

#include "lib/fs_visitor.h"
#include "lib/link.h"
#include "lib/file.h"
#include "lib/directory.h"

namespace fs {

class SizeCountingVisitor : public FSVisitor {
 private:
  unsigned int total_size_ = 0;

 public:
  void visit(const std::shared_ptr<Link>& link) { total_size_ += link->getDiskUtil(); }
  void visit(const std::shared_ptr<Directory>& dir) { total_size_ += dir->getDiskUtil(); }
  void visit(const std::shared_ptr<File>& file) { total_size_ += file->getDiskUtil(); }
  unsigned getTotalSize() const { return total_size_; }
};
}  // end of namespace fs

#endif  // SIZE_COUNTING_VISITOR_H
