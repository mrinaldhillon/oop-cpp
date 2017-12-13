#ifndef NULL_REPLACEMENT_H
#define NULL_REPLACEMENT_H

#include <memory>
#include <queue>
#include "lib/cache_replacement_policy.h"
#include "lib/file.h"

namespace fs {

class NullReplacement : public CacheReplacementPolicy {
 private:
  NullReplacement(){};

 public:
  NullReplacement(const NullReplacement&) = delete;
  NullReplacement& operator=(const NullReplacement&) = delete;
  void replace(
      std::unordered_map<std::string, std::unique_ptr<fs::File>>&,
      std::unique_ptr<fs::File>&) {};
  void insert(std::unordered_map<std::string, std::unique_ptr<fs::File>>&,
              std::unique_ptr<fs::File>&) {};
  static NullReplacement& getInstance() {
    static NullReplacement instance_;
    return instance_;
  }
};

}  // end of namespace fs

#endif  // NULL_REPLACEMENT_H
