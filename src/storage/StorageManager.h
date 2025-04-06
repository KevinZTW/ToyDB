//
// Created by Kevin Zhang on 2025/2/23.
//

#ifndef TOY_DB_STORAGEMANAGER_H
#define TOY_DB_STORAGEMANAGER_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include "common/Config.h"
#include "buffer/Page.h"

namespace DB {
class StorageManager {
 public:
  StorageManager(bool truncate_mode = true);

  ~StorageManager();

  void ExtendTo(int page_num);

  int GetTotalPageNum();

  void ReadPage(PageID page_id, char *page_data);
  void WritePage(PageID page_id, const char *page_data);

 private:
  const std::string database_filename_ = DB_FILE_NAME;
  std::fstream file_stream_;
  int total_page_num_ = 0;
  std::mutex io_mutex_;

};
}

#endif //TOY_DB_STORAGEMANAGER_H
