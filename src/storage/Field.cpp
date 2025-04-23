//
// Created by Kevin Zhang on 2025/2/24.
//

#include "Field.h"

enum FieldType {
  STRING,
  FLOAT
};

class Field {
 public:
  FieldType type;
  std::unique_ptr<char[]> data;
  size_t data_length;

 public:
  Field(float f) : type(FieldType::FLOAT) {
    data_length = sizeof(float);
    data = std::make_unique<char[]>(data_length);
    memcpy(data.get(), &f, data_length);
  }

  Field(const char *str) : type(FieldType::STRING) {
    data_length = strlen(str) + 1; // +1 for null terminator
    data = std::make_unique<char[]>(data_length);
    memcpy(data.get(), str, data_length);
  }
};