#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <iterator>
#include <regex>
#include "lib/command.h"
#include "lib/file_system.h"

namespace fs {

class Search : public Command {
 private:
  const FileSystem* fs_;
  const std::string name_ = "search";
  std::string options_;

 public:
  Search(const FileSystem& fs, const std::string& options)
      : fs_(&fs), options_(options) {}
  Search(const Search& rhs) : fs_(rhs.fs_), options_(rhs.options_) {}
  Search& operator=(const Search& rhs) {
    fs_ = rhs.fs_;
    options_ = rhs.options_;
    return *this;
  }

  std::string getName() const { return name_; }
  std::string getOptions() const { return options_; }

  void execute() {
    if (options_.empty()) {
      throw std::invalid_argument(
          "search: Invalid input argument\nExpected: search .extension | "
          "search .extension directory_path");
    }
    std::vector<std::string> options;
    std::regex ws_re("\\s+");
    std::copy(
        std::sregex_token_iterator(options_.begin(), options_.end(), ws_re, -1),
        std::sregex_token_iterator(), std::back_inserter(options));

    if (options.size() > 2) {
      throw std::invalid_argument(
          "search: Invalid input argument\nExpected: search .extension | "
          "search .extension directory_path");
    }
    std::vector<std::shared_ptr<File>> files;
    if (options.size() == 1) {
      files = fs_->searchFileTypes(options.front());
    } else {
      auto fs_element = fs_->getElement(options.back());
      if (nullptr == fs_element) {
        throw std::range_error("search: " + options.back() +
                               " No such file or directory");
      }
      if (fs_element->isFile()) {
        throw std::runtime_error("search: " + options.back() +
                                 " cannot be executed on a file");
      }
      files = fs_->searchFileTypes(dynamic_cast<Directory&>(*fs_element),
                                   options.front());
    }

    for (auto file : files) {
      std::cout << file->getName() << "\n";
    }
  }
};

}  // end of namespace

#endif  // SEARCH_H
