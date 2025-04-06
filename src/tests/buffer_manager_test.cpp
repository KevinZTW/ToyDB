//
// Created by Kevin Zhang on 2025/2/24.
//
#include <gtest/gtest.h>
#include "buffer/BufferManager.h"

TEST(BufferManagerTest, Basic) {
  std::unique_ptr<DB::BufferManager> buffer_manager = std::make_unique<DB::BufferManager>();

  buffer_manager->FetchPage(0);
}