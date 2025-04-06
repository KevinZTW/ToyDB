//
// Created by Kevin Zhang on 2025/4/6.
//

#ifndef TOY_DB_SRC_BUFFER_TWOQBUFFERPOLICY_H_
#define TOY_DB_SRC_BUFFER_TWOQBUFFERPOLICY_H_

#include "BufferPolicy.h"
#include "mutex"
#include "list"

namespace DB {
class TwoQBufferPolicy : public BufferPolicy {

 public:
  TwoQBufferPolicy(std::function<bool(PageID)> page_is_evictable, size_t cache_size)
      : cache_size(cache_size), pageIsEvictable(page_is_evictable) {}

  ~TwoQBufferPolicy() = default;

  friend class BufferManager;

 public:
  PageID evict() override {
    std::lock_guard lock(mx);

    for (auto it = FIFO.begin(); it != FIFO.end(); ++it) {
      PageID id = *it;
      if (pageIsEvictable(id)) {
        FIFO.erase(it);
        pageMap.erase(id);
        return id;
      }
    }

    for (auto it = LRU.rbegin(); it != LRU.rend(); ++it) {
      PageID id = *it;
      if (pageIsEvictable(id)) {
        LRU.erase(std::next(it).base());
        pageMap.erase(id);
        return id;
      }
    }

    return INVALID_PAGE_ID;
  }

  bool touch(PageID pageId) override {
    std::lock_guard lock(mx);
    // page exist in cache
    if (pageMap.find(pageId) != pageMap.end()) {
      auto FIFO_it = std::find(FIFO.begin(), FIFO.end(), pageId);
      // exist in FIFO queue
      if (FIFO_it != FIFO.end()) {
        FIFO.erase(FIFO_it);
        LRU.push_front(pageId);
        pageMap[pageId] = LRU.begin();

        return true;
      } else {
        // in LRU, move to front
        auto it = pageMap[pageId];
        LRU.erase(it);
        LRU.push_front(pageId);
        pageMap[pageId] = LRU.begin();

        return true;
      }
    }

    FIFO.push_back(pageId);
    pageMap[pageId] = std::prev(FIFO.end());

    return true;
  }
 private:
  std::mutex mx;
  std::list<PageID> FIFO; // start from "front"
  std::list<PageID> LRU; //  "front" is the most recent
  std::unordered_map<PageID, std::list<PageID>::iterator> pageMap;
  size_t cache_size;

  std::function<bool(PageID)> pageIsEvictable;
};
}
#endif //TOY_DB_SRC_BUFFER_TWOQBUFFERPOLICY_H_
