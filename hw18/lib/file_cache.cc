#include "lib/file_cache.h"
#include <memory>
#include "lib/file.h"

namespace fs {

#define FETCH_FROM_DISK(target_file) std::make_unique<File>(target_file)

std::string FileCache::fetch(const std::string& target_file) {
  try {
    return cache_.at(target_file)->read();
  } catch (const std::out_of_range& e) {
    std::unique_ptr<File> file = FETCH_FROM_DISK(target_file);
    std::string data = file->read();
    if (cache_.size() < cache_threshhold_) {
      insert(file);
    } else {
      replace(file);
    }
    return data;
  }
}

bool FileCache::isCached(const std::string& target_file) const {
  try {
    cache_.at(target_file);
    return true;
  } catch (const std::out_of_range& e) {
    return false;
  }
}

}  // end of namespace fs
