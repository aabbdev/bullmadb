#ifndef CDATABASE_H_
#define CDATABASE_H_

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <sstream>
#include <vector>
#include <filesystem>

#include <msgpack.hpp>
#include <rocksdb/db.h>

#include "table.h"

namespace fs = std::filesystem;

class CDatabase
{
public:
    //std::map<std::string, rocksdb::ColumnFamilyHandle> tables;
    std::string name;
    rocksdb::DB* db;
    std::map<std::string, CTable*> tables;
    CTable* table_get(std::string);
    CTable* table_create(std::string);
    bool table_drop(std::string);
    CDatabase(fs::path);
    ~CDatabase();
};
#endif // CDATABASE_H_