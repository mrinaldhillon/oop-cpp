#ifndef CP_H
#define CP_H

#include <iterator>
#include <regex>
#include "lib/command.h"
#include "lib/directory.h"
#include "lib/file.h"
#include "lib/file_system.h"
#include "lib/link.h"

namespace fs {

class Cp : public Command {
 private:
  FileSystem* fs_;
  const std::string name_ = "cp";
  std::string options_;

 public:
  Cp(FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Cp(const Cp& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Cp& operator=(const Cp& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  // only copies, does not append element to dst dir
  std::shared_ptr<FSElement> copy_element(
      const FSElement& src, const std::string& dst_name,
      const std::shared_ptr<Directory>& dst_parent_element) {
    if (src.isFile()) {
      auto copied_element =
          std::make_shared<File>(dst_parent_element, dst_name,
                                 dst_parent_element->getOwner(), src.getSize());
      return copied_element;
    }
    auto copied_element = std::make_shared<Directory>(
        dst_parent_element, dst_name, dst_parent_element->getOwner());
    for (auto child : dynamic_cast<const Directory&>(src).getChildren()) {
      auto copied_child =
          copy_element(*child, child->getName(), copied_element);
      fs_->addChild(*copied_element, copied_child);
    }
    return copied_element;
  }

  // TODO: Currently if src and dst elements are same type, dst is overwritten
  void copy_src_to_dst_dir(const std::string& dst_dir_path,
                           std::shared_ptr<FSElement> src_fs_element,
                           std::shared_ptr<Directory> dst_dir_element) {
    auto src_name = src_fs_element->getName();
    auto copied_element =
        copy_element(*src_fs_element, src_name, dst_dir_element);

    for (auto child : dst_dir_element->getChildren()) {
      if (child->getName() == src_name) {
        if (child->isFile()) {
          if (src_fs_element->isFile()) {  // overwrite
            dst_dir_element->rmChild(child->getName());
            fs_->addChild(*dst_dir_element, copied_element);
            return;
          } else {
            // directory cannot overwrite file
            throw std::runtime_error("cp: cannot overwrite not directory" +
                                     dst_dir_path + "/" + child->getName() +
                                     ": with directory");
          }
        } else {
          if (src_fs_element->isFile()) {
            // file cannot overwrite directory
            throw std::runtime_error("cp: cannot overwrite " + dst_dir_path +
                                     "/" + child->getName() +
                                     ": with non directory");
          } else {
            dst_dir_element->rmChild(child->getName());
            fs_->addChild(*dst_dir_element, copied_element);
            return;
          }
        }
      }
    }
    // if dst does not contain child of same name, simple addChild
    fs_->addChild(*dst_dir_element, copied_element);
  }

  void execute() {
    std::vector<std::string> options;
    if (options_.empty()) throw std::invalid_argument("cp: missing operand");
    std::regex ws_re("\\s+");
    std::copy(
        std::sregex_token_iterator(options_.begin(), options_.end(), ws_re, -1),
        std::sregex_token_iterator(), std::back_inserter(options));

    if (options.size() != 2) {
      throw std::invalid_argument("cp: invalid input arguments");
    }

    auto dst_dir_path = options.back();
    auto src_path = options.front();

    auto src_fs_element = fs_->getElement(src_path);
    if (nullptr == src_fs_element) {
      throw std::runtime_error("cp: cannot copy " + src_path +
                               ": Src file/dir not found");
    }
    auto dst_fs_element = fs_->getElement(dst_dir_path);
    if (nullptr == dst_fs_element) {
      throw std::runtime_error("cp: cannot copy " + dst_dir_path +
                               ": dest dir not found");
    }

    if (dst_fs_element->isFile()) {
      throw std::runtime_error("cp: cannot copy " + dst_dir_path +
                               ": destination path is a file");
    }

    auto dst_dir_element = std::dynamic_pointer_cast<Directory>(dst_fs_element);
    copy_src_to_dst_dir(dst_dir_path, src_fs_element, dst_dir_element);
  }
};

}  // end of namespace

#endif  // CP_H
