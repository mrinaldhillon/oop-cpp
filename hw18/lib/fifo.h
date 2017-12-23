#ifndef FIFO_H
#define FIFO_H

#include <memory>
#include <queue>
#include "lib/file.h"
#include "lib/file_cache.h"

namespace fs {

class FIFO : public FileCache {
 private:
  FIFO(){};
  std::queue<std::string> cache_associated_fifo_queue_{};

 protected:
  void insert(std::unique_ptr<fs::File>&);
  void replace(std::unique_ptr<fs::File>&);

 public:
  FIFO(const FIFO&) = delete;
  FIFO& operator=(const FIFO&) = delete;

  static FIFO& getInstance() {
    static FIFO instance_;
    return instance_;
  }
};

}  // end of namespace fs

#endif  // FIFO_H
