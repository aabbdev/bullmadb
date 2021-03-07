#ifndef __CTABLE_H__
#define __CTABLE_H__

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <sstream>
#include <vector>

#include <msgpack.hpp>
#include <rocksdb/db.h>

class CTable
{
public:
    std::string name;
    std::map<std::string, rocksdb::ColumnFamilyHandle*> indexes;
    CTable(rocksdb::DB*, rocksdb::ColumnFamilyHandle*);
    ~CTable();
    rocksdb::ColumnFamilyHandle* getHandle();
private:
    rocksdb::ColumnFamilyHandle* handle;
    rocksdb::DB* db;
};
#endif // __CTABLE_H__