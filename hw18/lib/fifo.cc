#include "lib/fifo.h"

namespace fs {

void FIFO::insert(std::unique_ptr<fs::File>& file) {
  cache_associated_fifo_queue_.push(file->getFilePath());
  cache_.insert(std::make_pair(file->getFilePath(), std::move(file)));
}

void FIFO::replace(std::unique_ptr<fs::File>& file) {
  if (false == cache_associated_fifo_queue_.empty()) {
    std::string file_path = cache_associated_fifo_queue_.front();
    cache_associated_fifo_queue_.pop();
    cache_.erase(file_path);
  }
  insert(file);
}
}  // end of namespace fs
