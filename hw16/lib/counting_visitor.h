#ifndef COUNTING_VISITOR_H
#define COUNTING_VISITOR_H

#include <memory>
#include "lib/fs_visitor.h"

namespace fs {

class CountingVisitor : public FSVisitor {
 private:
  int dir_num_ = 0;
  int file_num_ = 0;
  int link_num_ = 0;

 public:
  void visit(const std::shared_ptr<Link>&) { link_num_++; }
  void visit(const std::shared_ptr<Directory>&) { dir_num_++; }
  void visit(const std::shared_ptr<File>&) { file_num_++; }
  int getLinkNum() const { return link_num_; }
  int getFileNum() const { return file_num_; }
  int getDirNum() const { return dir_num_; }
};
}  // end of namespace fs

#endif  // COUNTING_VISITOR_H
