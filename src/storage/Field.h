//
// Created by Kevin Zhang on 2025/2/24.
//

#ifndef TOY_DB_FIELD_H
#define TOY_DB_FIELD_H

#include <memory>

namespace DB {
enum FieldType {
  INT,
  STRING,
  FLOAT
};

class Field {
  FieldType type;
  std::unique_ptr<char[]> data;
  size_t data_length;

 public:
  Field(int i) : type(FieldType::INT) {
    data_length = sizeof(int);
    data = std::make_unique<char[]>(data_length);
    memcpy(data.get(), &i, data_length);
  }

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
}

#endif //TOY_DB_FIELD_H
