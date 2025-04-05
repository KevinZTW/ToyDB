//
// Created by Kevin Zhang on 2025/2/23.
//
#include "StorageManager.h"
#include "Config.h"

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

  // move to the end of the file
  file_stream.seekg(0, std::ios::end);
  page_num = file_stream.tellg() / PAGE_SIZE;

  if (page_num == 0) {
    Extend(1024);
  }
}
DB::StorageManager::~StorageManager() {

  if (file_stream.is_open()) {
    file_stream.close();
  }
}

void DB::StorageManager::Extend(int to_page_num) {
  std::lock_guard<std::mutex> io_guard(io_mutex);
  int write_size = std::max(0, to_page_num - page_num) * PAGE_SIZE;

  if (write_size > 0) {
    char *buffer = new char[write_size];
    std::memset(buffer, 0, write_size);

    file_stream.seekp(0, std::ios::end);
    file_stream.write(buffer, write_size);
    file_stream.flush();

    page_num = to_page_num;
  }
}

int DB::StorageManager::GetPageNum() {
  return page_num;
}

