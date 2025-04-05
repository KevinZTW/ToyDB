//
// Created by Kevin Zhang on 2025/2/24.
//
#include <gtest/gtest.h>
#include "core/StorageManager.h"

TEST(StorageManagerTest, Construction) {
  EXPECT_NO_THROW(DB::StorageManager storage_manager_manager(false));
  EXPECT_NO_THROW(DB::StorageManager storage_manager_manager(true));
}

TEST(StorageManagerTest, InitailStorageShouldHave1024Pages) {
  DB::StorageManager storage_manager(true);
  ASSERT_EQ(storage_manager.GetPageNum(), 1024);
}

TEST(StorageManagerTest, ExtendStorage) {
  DB::StorageManager storage_manager(true);
  ASSERT_EQ(storage_manager.GetPageNum(), 1024);
  storage_manager.Extend(2048);
  ASSERT_EQ(storage_manager.GetPageNum(), 2048);
  storage_manager.Extend(4096);
  ASSERT_EQ(storage_manager.GetPageNum(), 4096);

  DB::StorageManager storage_manager_2(false);
  ASSERT_EQ(storage_manager_2.GetPageNum(), 4096);
}