//
// Created by Kevin Zhang on 2025/2/24.
//

#ifndef TOY_DB_TUPLE_H
#define TOY_DB_TUPLE_H
#include "vector"
#include "Field.h"

namespace DB {
class Tuple {
 public:
  Tuple() = default;

  void AddField(std::unique_ptr<Field> field) {
    fields.push_back(std::move(field));
  }

 private:
  std::vector<std::unique_ptr<Field>> fields;
};
}

#endif //TOY_DB_TUPLE_H
