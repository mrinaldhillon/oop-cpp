#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "lib/libfile_cache.h"

namespace fs {
namespace {

class FileCacheTest : public ::testing::Test {
 protected:
  const std::string file1_ = "/dummy_file1.txt";
  const std::string file2_ = "/dummy_file2.txt";
  const std::string file3_ = "/dummy_file3.txt";
  FIFO& file_cache_ = FIFO::getInstance();
};

TEST_F(FileCacheTest, singletonInstantiation) {
  EXPECT_THAT(file_cache_, ::testing::Ref(FIFO::getInstance()));
}

TEST_F(FileCacheTest, fetchFromDiskANDSubsequentlyFetchFromCache) {
  std::string data = file_cache_.fetch(file1_);
  EXPECT_TRUE(file_cache_.isCached(file1_));
  EXPECT_EQ(data, file_cache_.fetch(file1_));
}

TEST_F(FileCacheTest, replaceCache) {
  file_cache_.fetch(file1_);
  file_cache_.fetch(file2_);
  EXPECT_TRUE(file_cache_.isCached(file1_));
  file_cache_.fetch(file3_);
  EXPECT_TRUE(file_cache_.isCached(file3_));
  EXPECT_FALSE(file_cache_.isCached(file1_));
}

}  // end of unnamed namespace
}  // end of namespace fs
