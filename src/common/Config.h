//
// Created by Kevin Zhang on 2025/4/5.
//

#ifndef TOY_DB_SRC_CORE_CONFIG_H_
#define TOY_DB_SRC_CORE_CONFIG_H_
#pragma once

#include <cstddef>

namespace DB {

inline constexpr int INVALID_PAGE_ID = -1;
inline constexpr int PAGE_SIZE = 4096;
inline constexpr const char *DB_FILE_NAME = "toy_db.data";

using PageID = uint32_t;
using FrameID = uint32_t;

class Config {

};
}
#endif //TOY_DB_SRC_CORE_CONFIG_H_
