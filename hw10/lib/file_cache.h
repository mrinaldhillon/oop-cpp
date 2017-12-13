#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include <memory>
#include <unordered_map>
#include "lib/cache_replacement_policy.h"
#include "lib/file.h"

namespace fs {

#ifndef MAX_CACHE
#define MAX_CACHE 2
#endif  // MAX_CACHE

class FileCache final {
 private:
  FileCache() {};
  unsigned int cache_threshhold_ = MAX_CACHE;
  std::unordered_map<std::string, std::unique_ptr<fs::File>> cache_{};
  CacheReplacementPolicy* replacement_policy_ = nullptr;
  void replace(const fs::File&);

 public:
  FileCache(const FileCache&) = delete;
  FileCache& operator=(const FileCache) = delete;
  static FileCache& getInstance() {
    static FileCache instance_;
    return instance_;
  }
  std::string fetch(const std::string& target_file);
  void setReplacementPolicy(CacheReplacementPolicy& replacement_policy);
  bool isCached(const std::string& target_file) const;
};

}  // end of namespace fs

#endif  // FILE_CACHE_H
