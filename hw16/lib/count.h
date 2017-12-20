#ifndef COUNT_H
#define COUNT_H

#include <iostream>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Count : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "count";
  std::string options_;

 public:
  Count(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Count(const Count& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Count& operator=(const Count& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void print(std::tuple<int, int, int>& counts) {
    std::cout << "Dirs :" << std::get<0>(counts) << ", "
              << "Files :" << std::get<1>(counts) << ", "
              << "Links :" << std::get<2>(counts) << "\n";
  }

  void execute() {
    std::tuple<int, int, int> counts;
    if (options_.empty()) {
      counts = fs_->countDirsFilesLinks();
      print(counts);
      return;
    }

    auto fs_element = fs_->getElement(options_);
    if (nullptr == fs_element) {
      throw std::range_error("count: " + options_ +
                             " No such file or directory");
    }
    if (fs_element->isFile()) {
      throw std::runtime_error("count: " + options_ +
                               " cannot be executed on a file");
    }

    counts = fs_->countDirsFilesLinks(dynamic_cast<Directory&>(*fs_element));
    print(counts);
  }
};

}  // end of namespace

#endif  // COUNT_H
