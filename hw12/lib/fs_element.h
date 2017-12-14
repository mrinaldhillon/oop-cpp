#ifndef FS_ELEMENT_H
#define FS_ELEMENT_H

#include <ctime>
#include <memory>
#include <string>
#include <vector>

namespace fs {

class FSElement {
 protected:
  std::weak_ptr<FSElement> parent_;
  std::string name_;
  std::string owner_;
  const std::time_t created_;
  std::time_t last_modified_;
  unsigned int size_;

 public:
  FSElement(const std::shared_ptr<FSElement>& parent, const std::string& name,
            const std::string& owner);
  FSElement(const FSElement&) = default;
  FSElement(FSElement&&) = default;
  FSElement& operator=(const FSElement&) = default;
  FSElement& operator=(FSElement&&) = default;
  virtual ~FSElement() = default;

  virtual std::weak_ptr<FSElement> getParent() const;
  virtual bool isFile() const = 0;
  virtual unsigned int getSize() const;
  virtual void setSize(unsigned int);
  virtual const std::string& getName() const;
  virtual const std::string& getOwner() const;
  virtual const std::time_t& getModTime() const;
  virtual const std::time_t& getCreationTime() const;
  virtual const std::vector<std::shared_ptr<FSElement>> getChildren() const = 0;
  virtual void appendChild(std::shared_ptr<FSElement>) = 0;
  virtual void setModTime(std::time_t&);
};

}  // end of namespace fs
#endif  // FS_ELEMENT_H
