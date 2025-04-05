//
// Created by Kevin Zhang on 2025/4/5.
//

#ifndef TOY_DB_SRC_CORE_CONFIG_H_
#define TOY_DB_SRC_CORE_CONFIG_H_
#pragma once

#include <cstddef>
namespace DB {
inline constexpr size_t PAGE_SIZE = 4096;
inline constexpr const char *DB_FILE_NAME = "toy_db.data";
}
#endif //TOY_DB_SRC_CORE_CONFIG_H_
