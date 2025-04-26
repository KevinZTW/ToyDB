//
// Created by Kevin Zhang on 2025/2/17.
//

#ifndef TOY_DB_BUFFERMANAGER_H
#define TOY_DB_BUFFERMANAGER_H

#include "common/Config.h"
#include "storage/StorageManager.h"
#include "vector"
#include <shared_mutex>
#include "BufferPolicy.h"
#include "TwoQBufferPolicy.h"
#include "SlottedPage.h"

namespace DB {
enum class PageLockMode { EXCLUSIVE, SHARED };
class buffer_full_error : public std::exception {
 public:
  const char *what() const noexcept override { return "buffer is full"; }
};
class BufferManager {
  struct BufferFrame {
    BufferFrame(FrameID frame_id)
        : frame_id(frame_id) {}

    FrameID frame_id;
    PageID page_id = INVALID_PAGE_ID;
    std::shared_ptr<DB::SlottedPage> page_ = nullptr;
    bool is_dirty_ = false;
  };

 private:

  std::unique_ptr<BufferPolicy> policy_ = std::make_unique<TwoQBufferPolicy>(
      [this](PageID page_id) {
        return page_use_count[page_id] == 0;
      },
      BUFFER_MANAGER_POOL_SIZE);

  //TODO: Implement a page_id allocation strategy
  uint32_t capacity_ = BUFFER_MANAGER_POOL_SIZE;
  PageID next_page_id_ = 0;
  StorageManager storage_manager_{false};
  std::vector<BufferFrame> buffer_frames_;
  std::unordered_map<PageID, PageLockMode> lock_status;
  std::unordered_map<PageID, FrameID> page_to_frame_id_;
  std::unordered_map<PageID, std::atomic<int>> page_use_count;

  std::unordered_map<PageID, std::shared_mutex> page_locks;

  //TODO: change to fine grained lock
  std::mutex main_mx;

 public:
  BufferManager();
  ~BufferManager();

  std::shared_ptr<DB::SlottedPage> FetchPage(PageID page_id, bool exclusive = false);

  void UnfixPage(PageID page_id, bool is_dirty);
};
}
#endif //TOY_DB_BUFFERMANAGER_H
