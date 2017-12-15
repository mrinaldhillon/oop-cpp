#ifndef FS_VISITOR_H
#define FS_VISITOR_H

#include <memory>

namespace fs {
class Link;
class Directory;
class File;

class FSVisitor {
 public:
  FSVisitor() = default;
  FSVisitor(const FSVisitor&) = default;
  FSVisitor(FSVisitor&&) = default;
  FSVisitor& operator=(const FSVisitor&) = default;
  FSVisitor& operator=(FSVisitor&&) = default;
  virtual ~FSVisitor() = default;

  virtual void visit(const std::shared_ptr<Link>&) = 0;
  virtual void visit(const std::shared_ptr<Directory>&) = 0;
  virtual void visit(const std::shared_ptr<File>&) = 0;
};

}  // end of namespace fs

#endif  // FS_VISITOR_H
