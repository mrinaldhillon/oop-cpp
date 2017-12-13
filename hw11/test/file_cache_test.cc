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
  FileCache& file_cache_ = FileCache::getInstance();
};

TEST_F(FileCacheTest, singletonInstantiation) {
  EXPECT_THAT(file_cache_, ::testing::Ref(FileCache::getInstance()));
}

TEST_F(FileCacheTest, fetchFromDiskWithNullReplaceMentPolicy) {
  std::string data = file_cache_.fetch(file1_);
  EXPECT_EQ(data, file_cache_.fetch(file1_));
  EXPECT_FALSE(file_cache_.isCached(file1_));
}

TEST_F(FileCacheTest, fetchFromDiskANDSubsequentlyFetchFromCachewithFIFOPolicy) {
  file_cache_.setReplacementPolicy(FIFO::getInstance());
  std::string data = file_cache_.fetch(file1_);
  EXPECT_TRUE(file_cache_.isCached(file1_));
  EXPECT_EQ(data, file_cache_.fetch(file1_));
}

TEST_F(FileCacheTest, replaceCacheBasedOnFIFOPolicy) {
  file_cache_.setReplacementPolicy(FIFO::getInstance());
  file_cache_.fetch(file1_);
  file_cache_.fetch(file2_);
  EXPECT_TRUE(file_cache_.isCached(file1_));
  file_cache_.fetch(file3_);
  EXPECT_TRUE(file_cache_.isCached(file3_));
  EXPECT_FALSE(file_cache_.isCached(file1_));
}

}  // end of unnamed namespace
}  // end of namespace fs
