#include "lib/file.h"
#include <random>

namespace fs {

File::File(const std::string& file_path)
    : file_path_(file_path), data_("data in dummy file" + file_path) {}

std::string File::getFilePath() const { return file_path_; }
std::string File::read() const { return data_; }

}  // end of namespace fs
