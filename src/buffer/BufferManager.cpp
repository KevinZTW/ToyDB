//
// Created by Kevin Zhang on 2025/2/17.
//

#include "BufferManager.h"
#include "common/Config.h"

DB::BufferManager::BufferManager() {
  storage_manager_.ExtendTo(BUFFER_MANAGER_POOL_SIZE);

  buffer_frames_.reserve(BUFFER_MANAGER_POOL_SIZE);
  for (int i = 0; i < BUFFER_MANAGER_POOL_SIZE; i++) {
    buffer_frames_.emplace_back(static_cast<FrameID>(i));
  }

}
DB::BufferManager::~BufferManager() {
  for (auto &frame : buffer_frames_) {
    if (frame.is_dirty) {
      storage_manager_.WritePage(frame.page_id, frame.page->data_.get());
    }
  }
}

std::shared_ptr<DB::Page> DB::BufferManager::FetchPage(int page_id, bool exclusive) {
  // super coarse grained lock... should enhance to fine-grained lock
  main_mx.lock();

  auto it = page_to_frame_id_.find(page_id);
  // page exist in cache
  if (it != page_to_frame_id_.end()) {
    page_use_count[page_id]++;

    if (exclusive) {
      page_locks[page_id].lock();
      lock_status[page_id] = PageLockMode::EXCLUSIVE;
    } else {
      page_locks[page_id].lock_shared();
      lock_status[page_id] = PageLockMode::SHARED;
    }

    //    policy->touch(page_id);

    main_mx.unlock();

    return buffer_frames_[it->second].page;
  }


  // no capacity, get from someone else
  if (page_to_frame_id_.size() >= capacity_) {
    PageID old_page_id = policy_->evict();
    if (old_page_id == INVALID_PAGE_ID) {
      main_mx.unlock();
      throw buffer_full_error{};
    }
    FrameID frame_id = page_to_frame_id_[old_page_id];
    BufferFrame &frame = buffer_frames_[frame_id];

    if (frame.is_dirty) {
      storage_manager_.WritePage(old_page_id, frame.page->data_.get());
    }

    storage_manager_.ReadPage(page_id, frame.page->data_.get());
    frame.page_id = page_id;

    page_use_count[page_id]++;
    if (page_locks.find(page_id) == page_locks.end()) {
      page_locks.try_emplace(page_id);
    }
    if (exclusive) {
      page_locks[page_id].lock();
      lock_status[page_id] = PageLockMode::EXCLUSIVE;
    } else {
      page_locks[page_id].lock_shared();
      lock_status[page_id] = PageLockMode::SHARED;
    }
    page_to_frame_id_[page_id] = frame_id;
    page_to_frame_id_.erase(old_page_id);
//    policy->touch(page_id);
    main_mx.unlock();

    return frame.page;
  }

  // find empty slot
  // 先用最 naive 的 linear scan
  for (size_t i = 0; i < capacity_; i++) {
    BufferFrame &frame = buffer_frames_[i];
    if (frame.page == nullptr) {
      storage_manager_.ReadPage(page_id, frame.page->data_.get());
      frame.page_id = page_id;
      page_use_count[page_id]++;
      if (exclusive) {
        page_locks[page_id].lock();
        lock_status[page_id] = PageLockMode::EXCLUSIVE;
      } else {
        page_locks[page_id].lock_shared();
        lock_status[page_id] = PageLockMode::SHARED;
      }

      page_to_frame_id_[page_id] = i;
      policy_->touch(page_id);
      main_mx.unlock();

      return frame.page;
    }
  }
  main_mx.unlock();
  throw buffer_full_error{};
}
void DB::BufferManager::FlushPage(int page_id) {

}
void DB::BufferManager::UnfixPage(int page_id, bool is_dirty) {

}

