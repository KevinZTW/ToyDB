//
// Created by Kevin Zhang on 2025/2/23.
//

#ifndef TOY_DB_STORAGEMANAGER_H
#define TOY_DB_STORAGEMANAGER_H

#include <fstream>
#include <filesystem>
#include <iostream>

namespace DB {
class StorageManager {
 public:
  StorageManager(bool truncate_mode = true);

 private:
  const std::string database_filename = "toy_db.data";
  std::fstream file_stream;
};
}

#endif //TOY_DB_STORAGEMANAGER_H
