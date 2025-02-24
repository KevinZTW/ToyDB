//
// Created by Kevin Zhang on 2025/2/24.
//

#ifndef TOY_DB_FIELD_H
#define TOY_DB_FIELD_H

#include <memory>

namespace DB {
    enum FieldType
    {
        STRING,
        FLOAT
    };

    class Field {
        FieldType type;
        std::unique_ptr<char[]> data;
        size_t data_length;

    public:
        Field(float f) : type(FieldType::FLOAT) {
            data_length = sizeof(float);
            data = std::make_unique<char[]>(data_length);
        }

    };
}


#endif //TOY_DB_FIELD_H
