#ifndef CACHE_REPLACEMENT_POLICY_H
#define CACHE_REPLACEMENT_POLICY_H

#include <memory>
#include <unordered_map>
#include "lib/file.h"

namespace fs {

class CacheReplacementPolicy {
 public:
  CacheReplacementPolicy(const CacheReplacementPolicy&) = default;
  CacheReplacementPolicy(CacheReplacementPolicy&&) = default;
  CacheReplacementPolicy& operator=(const CacheReplacementPolicy&) = default;
  CacheReplacementPolicy& operator=(CacheReplacementPolicy&&) = default;
  CacheReplacementPolicy() = default;
  virtual ~CacheReplacementPolicy() = default;

  virtual void insert(
      std::unordered_map<std::string, std::unique_ptr<fs::File>>&,
      std::unique_ptr<fs::File>&) = 0;
  virtual void replace(
      std::unordered_map<std::string, std::unique_ptr<fs::File>>&,
      std::unique_ptr<fs::File>&) = 0;
};

}  // end of namespace fs

#endif  // CACHE_REPLACEMENT_POLICY_H
