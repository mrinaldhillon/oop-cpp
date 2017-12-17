#ifndef FS_ELEMENT_H
#define FS_ELEMENT_H

#include <ctime>
#include <memory>
#include <string>
#include <vector>
#include "lib/fs_visitor.h"

namespace fs {

enum class FSElementType { file, dir, link };

class FSElement {
 protected:
  std::weak_ptr<Directory> parent_;
  std::string name_;
  std::string owner_;
  const std::time_t created_;
  std::time_t last_modified_;
  unsigned int size_;

 public:
  FSElement(const std::shared_ptr<Directory>& parent, const std::string& name,
            const std::string& owner);
  FSElement(const FSElement&) = default;
  FSElement(FSElement&&) = default;
  FSElement& operator=(const FSElement&) = default;
  FSElement& operator=(FSElement&&) = default;
  virtual ~FSElement() = default;
  virtual std::weak_ptr<Directory> getParent() const;
  virtual void setParent(const std::shared_ptr<Directory>&);
  virtual const std::string& getName() const;
  virtual void setName(const std::string&);
  virtual const std::string& getOwner() const;
  virtual void setOwner(const std::string&);
  virtual const std::time_t& getModTime() const;
  virtual void setModTime(const std::time_t&);
  virtual const std::time_t& getCreationTime() const;
  virtual bool isFile() const = 0;
  virtual unsigned int getSize() const = 0;
  virtual void accept(FSVisitor&) = 0;
  virtual unsigned int getDiskUtil() const = 0;
  // virtual const std::string& getInfo() const;
};

}  // end of namespace fs
#endif  // FS_ELEMENT_H
