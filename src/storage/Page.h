//
// Created by Kevin Zhang on 2025/4/5.
//

#ifndef TOY_DB_SRC_CORE_PAGE_H_
#define TOY_DB_SRC_CORE_PAGE_H_

#include <cstdint>
#include "common/Config.h"
#include <memory>

namespace DB {
class Page {
 public:
  virtual ~Page() = default;

  PageID page_id_ = INVALID_PAGE_ID;
  std::unique_ptr<char[]> data_ = std::make_unique<char[]>(PAGE_SIZE);
};
}

#endif //TOY_DB_SRC_CORE_PAGE_H_
