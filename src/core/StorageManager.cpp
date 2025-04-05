//
// Created by Kevin Zhang on 2025/2/23.
//
#include "StorageManager.h"

DB::StorageManager::StorageManager(bool truncate_mode) {

  if (!std::filesystem::exists(database_filename_)) {
    std::ofstream file(database_filename_);
    if (!file) {
      throw std::runtime_error("Failed to create database file.");
    }
    file.close();
    std::cout << "Database file created: " << database_filename_ << std::endl;
  }

  auto mode = std::ios::in | std::ios::out;
  if (truncate_mode) mode |= std::ios::trunc;
  file_stream_.open(database_filename_, mode);

  // move to the end of the file
  file_stream_.seekg(0, std::ios::end);
  total_page_num_ = file_stream_.tellg() / PAGE_SIZE;

  if (total_page_num_ == 0) {
    ExtendTo(1024);
  }
}
DB::StorageManager::~StorageManager() {

  if (file_stream_.is_open()) {
    file_stream_.close();
  }
}

void DB::StorageManager::ExtendTo(int page_num) {
  std::lock_guard<std::mutex> io_guard(io_mutex_);
  int write_size = std::max(0, page_num - total_page_num_) * PAGE_SIZE;

  if (write_size > 0) {
    char *buffer = new char[write_size];
    std::memset(buffer, 0, write_size);

    file_stream_.seekp(0, std::ios::end);
    file_stream_.write(buffer, write_size);
    file_stream_.flush();

    total_page_num_ = page_num;
  }
}

int DB::StorageManager::GetTotalPageNum() {
  return total_page_num_;
}

void DB::StorageManager::WritePage(PageID page_id, const char *page_data) {
  std::lock_guard<std::mutex> io_guard(io_mutex_);
  assert(page_id < total_page_num_);

  size_t page_offset = page_id * PAGE_SIZE;

  file_stream_.seekp(page_offset, std::ios::beg);
  file_stream_.write(page_data, PAGE_SIZE);
  file_stream_.flush();
}

void DB::StorageManager::ReadPage(PageID page_id, char *page_data) {
  std::lock_guard<std::mutex> io_guard(io_mutex_);
  assert(page_id < total_page_num_);

  file_stream_.seekg(page_id * PAGE_SIZE, std::ios::beg);

  // Read the content of the file into the page
  if (!file_stream_.read(page_data, PAGE_SIZE)) {
    std::cerr << "Error: [DB::StorageManager::ReadPage] Unable to read data from the file :: page id " << page_id
              << " \n";
    exit(-1);
  }
}

