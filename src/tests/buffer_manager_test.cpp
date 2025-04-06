//
// Created by Kevin Zhang on 2025/2/24.
//
#include <gtest/gtest.h>
#include "buffer/BufferManager.h"

TEST(BufferManagerTest, Basic) {
  std::unique_ptr<DB::BufferManager> buffer_manager = std::make_unique<DB::BufferManager>();
  ASSERT_NO_THROW(buffer_manager->FetchPage(0));
  ASSERT_NO_THROW(buffer_manager->UnfixPage(0, true));
}

TEST(BufferManagerTest, BasicPersistence) {
  size_t test_count = 10;

  {
    std::unique_ptr<DB::BufferManager> buffer_manager = std::make_unique<DB::BufferManager>();

    for (size_t i = 0; i < test_count; ++i) {
      auto page = buffer_manager->FetchPage(static_cast<DB::PageID>(i));
      ASSERT_NE(page, nullptr);
      //write data to page_
      char expected_value[DB::PAGE_SIZE];
      memset(expected_value, static_cast<char>('a' + i % 26), DB::PAGE_SIZE);

      memcpy(page->data_.get(), expected_value, DB::PAGE_SIZE);
      
      buffer_manager->UnfixPage(static_cast<DB::PageID>(i), true);
    }
  }
  {
    std::unique_ptr<DB::BufferManager> buffer_manager = std::make_unique<DB::BufferManager>();

    for (size_t i = 0; i < test_count; ++i) {
      auto page = buffer_manager->FetchPage(static_cast<DB::PageID>(i));
      ASSERT_NE(page, nullptr);

      char expected_value[DB::PAGE_SIZE];
      memset(expected_value, static_cast<char>('a' + i % 26), DB::PAGE_SIZE);

      for (size_t j = 0; j < DB::PAGE_SIZE; ++j) {
        ASSERT_EQ(page->data_[j], expected_value[j]);
      }

    }
  }
}