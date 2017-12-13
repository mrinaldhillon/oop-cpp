#ifndef FILE_H
#define FILE_H

#include <string>

namespace fs {

class File final {
 private:
  std::string file_path_;
  std::string data_;

 public:
  std::string getFilePath() const;
  File(const std::string& file_path);
  std::string read() const;
};

}  // end of namespace fs

#endif  // FILE_H
