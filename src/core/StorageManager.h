//
// Created by Kevin Zhang on 2025/2/23.
//

#ifndef TOY_DB_STORAGEMANAGER_H
#define TOY_DB_STORAGEMANAGER_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include "Config.h"

namespace DB {
class StorageManager {
 public:
  StorageManager(bool truncate_mode = true);

  ~StorageManager();

  void Extend(int to_page_num);

  int GetPageNum();
 private:
  const std::string database_filename = DB_FILE_NAME;
  std::fstream file_stream;
  int page_num = 0;
  std::mutex io_mutex;
};
}

#endif //TOY_DB_STORAGEMANAGER_H
