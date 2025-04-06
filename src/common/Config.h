//
// Created by Kevin Zhang on 2025/4/5.
//

#ifndef TOY_DB_SRC_CORE_CONFIG_H_
#define TOY_DB_SRC_CORE_CONFIG_H_
#pragma once

#include <cstddef>
#include "limits"

namespace DB {

inline constexpr uint32_t INVALID_PAGE_ID = std::numeric_limits<uint32_t>::max();
inline constexpr int PAGE_SIZE = 4096;
inline constexpr const char *DB_FILE_NAME = "toy_db.data";

inline constexpr int BUFFER_MANAGER_POOL_SIZE = 1024;

using PageID = uint32_t;
using FrameID = uint32_t;
}
#endif //TOY_DB_SRC_CORE_CONFIG_H_
