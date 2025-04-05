//
// Created by Kevin Zhang on 2025/2/24.
//
#include <gtest/gtest.h>
#include "core/Config.h"
#include "core/StorageManager.h"

TEST(StorageManagerTest, Construction) {
  EXPECT_NO_THROW(DB::StorageManager storage_manager_manager(false));
  EXPECT_NO_THROW(DB::StorageManager storage_manager_manager(true));
}

TEST(StorageManagerTest, InitailStorageShouldHave1024Pages) {
  DB::StorageManager storage_manager(true);
  ASSERT_EQ(storage_manager.GetTotalPageNum(), 1024);
}

TEST(StorageManagerTest, ExtendStorage) {
  DB::StorageManager storage_manager(true);
  ASSERT_EQ(storage_manager.GetTotalPageNum(), 1024);
  storage_manager.ExtendTo(2048);
  ASSERT_EQ(storage_manager.GetTotalPageNum(), 2048);
  storage_manager.ExtendTo(4096);
  ASSERT_EQ(storage_manager.GetTotalPageNum(), 4096);

  DB::StorageManager storage_manager_2(false);
  ASSERT_EQ(storage_manager_2.GetTotalPageNum(), 4096);
}

TEST(StorageManagerTest, WritePage) {
  DB::StorageManager storage_manager(true);

  char page_data[DB::PAGE_SIZE];

  for (int i = 0; i < DB::PAGE_SIZE; i++) {
    page_data[i] = static_cast<char>('a' + i % 26);
  }

  ASSERT_NO_THROW(storage_manager.WritePage(0, page_data));

  char read_data[DB::PAGE_SIZE];
  ASSERT_NO_THROW(storage_manager.ReadPage(0, read_data));
  ASSERT_EQ(std::memcmp(page_data, read_data, DB::PAGE_SIZE), 0);
}