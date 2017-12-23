#include "lib/file.h"
#include <memory>
#include <sstream>
#include <string>
#include "lib/directory.h"
#include "lib/fs_element.h"

namespace fs {

File::File(const std::shared_ptr<Directory>& parent, const std::string& name,
           const std::string& owner, unsigned int size)
    : FSElement(parent, name, owner) {
  size_ = size;
}

bool File::isFile() const { return true; }

void File::setSize(unsigned int size) { size_ = size; }

unsigned int File::getSize() const { return size_; }

void File::accept(FSVisitor& v) { v.visit(shared_from_this()); }

unsigned int File::getDiskUtil() const { return size_; }

std::string File::getInfo() const {
  auto mod_time = getModTime();
  std::ostringstream oss;
  oss << "file\t" << getOwner() << "\t" << getSize() << "\t"
      << std::asctime(std::localtime(&mod_time)) << "\t" << getName();
  return oss.str();
}

}  // end of namespace fs
