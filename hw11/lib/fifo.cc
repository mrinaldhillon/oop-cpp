#include "lib/fifo.h"

namespace fs {

void FIFO::insert(
    std::unordered_map<std::string, std::unique_ptr<fs::File>>& cache,
    std::unique_ptr<fs::File>& file) {
  cache_associated_fifo_queue_.push(file->getFilePath());
  cache.insert(std::make_pair(file->getFilePath(), std::move(file)));
}

void FIFO::replace(
    std::unordered_map<std::string, std::unique_ptr<fs::File>>& cache,
    std::unique_ptr<fs::File>& file) {
  if (false == cache_associated_fifo_queue_.empty()) {
    std::string file_path = cache_associated_fifo_queue_.front();
    cache_associated_fifo_queue_.pop();
    cache.erase(file_path);
  }
  insert(cache, file);
}

}  // end of namespace fs
