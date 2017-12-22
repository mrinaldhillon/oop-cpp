#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include <memory>
#include <unordered_map>
#include "lib/file.h"

namespace fs {

#ifndef MAX_CACHE
#define MAX_CACHE 2
#endif  // MAX_CACHE

class FileCache {
 private:
  unsigned int cache_threshhold_ = MAX_CACHE;
  void cacheFile(const fs::File& file);

 protected:
  virtual void replace(std::unique_ptr<fs::File>&) = 0;
  virtual void insert(std::unique_ptr<fs::File>&) = 0;
  std::unordered_map<std::string, std::unique_ptr<fs::File>> cache_{};

 public:
  std::string fetch(const std::string& target_file);
  bool isCached(const std::string& target_file) const;
};

}  // end of namespace fs

#endif  // FILE_CACHE_H
