//
// Created by Kevin Zhang on 2025/2/24.
//
#include <gtest/gtest.h>
#include "../StorageManager.h"

TEST(StorageManagerTest, BASIC_CONSTRUCTION) {
  EXPECT_NO_THROW(DB::StorageManager storage_manager_manager(false));
  EXPECT_NO_THROW(DB::StorageManager storage_manager_manager(true));
}