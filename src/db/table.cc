#include "table.h"

CTable::CTable(rocksdb::DB* _db, rocksdb::ColumnFamilyHandle* _cf){
    assert(_db != nullptr);
    assert(_cf != nullptr);

    db = _db;
    handle = _cf;
    name = _cf->GetName();
}
CTable::~CTable(){
    
}

rocksdb::ColumnFamilyHandle* CTable::getHandle(){
    return handle;
}