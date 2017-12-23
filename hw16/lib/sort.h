#ifndef SORT_H
#define SORT_H

#include <iostream>
#include "lib/alphabetical_comparator.h"
#include "lib/command.h"
#include "lib/file_system.h"
#include "lib/reverse_alphabetical_comparator.h"
#include "lib/timestamp_comparator.h"

namespace fs {

class Sort : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "sort";
  std::string options_;

 public:
  Sort(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Sort(const Sort& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Sort& operator=(const Sort& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void sort_and_print(Comparator& comp) {
    for (auto child : fs_->sort(*fs_->getCurrent(), comp)) {
      std::cout << child->getName() << std::endl;
    }
  }

  void execute() {
    if (options_.empty()) {
      AlphabeticalComparator comp;
      sort_and_print(comp);
    } else if (options_ == "reverse") {
      ReverseAlphabeticalComparator comp;
      sort_and_print(comp);
    } else if (options_ == "time") {
      TimestampComparator comp;
      sort_and_print(comp);
    } else {
      throw std::invalid_argument(
          "Invalid arguments: expected sort or sort reverse or sort time");
    }
  }
};

}  // end of namespace

#endif  // SORT_H
