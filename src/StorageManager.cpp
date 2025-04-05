//
// Created by Kevin Zhang on 2025/2/23.
//
#include "StorageManager.h"

DB::StorageManager::StorageManager(bool truncate_mode) {

  if (!std::filesystem::exists(database_filename)) {
    std::ofstream file(database_filename);
    if (!file) {
      throw std::runtime_error("Failed to create database file.");
    }
    file.close();
    std::cout << "Database file created: " << database_filename << std::endl;
  }

  auto mode = std::ios::in | std::ios::out;
  if (truncate_mode) mode |= std::ios::trunc;
  file_stream.open(database_filename, mode);

  if (!file_stream) {
    file_stream.clear();
    file_stream.open(database_filename, mode);
  }
}


