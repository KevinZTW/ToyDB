//
// Created by Kevin Zhang on 2025/4/6.
//

#ifndef TOY_DB_SRC_BUFFER_BUFFERPOLICY_H_
#define TOY_DB_SRC_BUFFER_BUFFERPOLICY_H_
#include "common/Config.h"

namespace DB {
class BufferPolicy {
 public:
  virtual bool touch(PageID page_id) = 0;
  virtual PageID evict() = 0;
  virtual ~BufferPolicy() = default;

  friend class BufferManager;
};
}
#endif //TOY_DB_SRC_BUFFER_BUFFERPOLICY_H_
