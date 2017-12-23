#ifndef FIFO_H
#define FIFO_H

#include <memory>
#include <queue>
#include "lib/cache_replacement_policy.h"
#include "lib/file.h"

namespace fs {

class FIFO : public CacheReplacementPolicy {
 private:
  FIFO(){};
  std::queue<std::string> cache_associated_fifo_queue_{};

 public:
  FIFO(const FIFO&) = delete;
  FIFO& operator=(const FIFO&) = delete;
  void replace(
      std::unordered_map<std::string, std::unique_ptr<fs::File>>& cache,
      std::unique_ptr<fs::File>&);
  void insert(std::unordered_map<std::string, std::unique_ptr<fs::File>>& cache,
              std::unique_ptr<fs::File>&);
  static FIFO& getInstance() {
    static FIFO instance_;
    return instance_;
  }
};

}  // end of namespace fs

#endif  // FIFO_H
