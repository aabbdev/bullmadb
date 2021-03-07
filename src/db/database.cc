#include "database.h"
#include "storage.h"

CDatabase::CDatabase(fs::path db_path) {
	name = db_path.filename().generic_string();
    CStorage* storage = CStorage::getInstance();
    rocksdb::Status status;
	std::vector<rocksdb::ColumnFamilyDescriptor> column_families;
	std::vector<rocksdb::ColumnFamilyHandle*> handles;
	if(fs::exists(db_path / fs::path("CURRENT"))){
		std::vector<std::string> families;
		status = rocksdb::DB::ListColumnFamilies(storage->options, db_path, &families);
		assert(status.ok());
		for (const auto & entry : families){
			column_families.push_back(rocksdb::ColumnFamilyDescriptor(entry, rocksdb::ColumnFamilyOptions()));
		}
	}else{
		column_families.push_back(rocksdb::ColumnFamilyDescriptor(rocksdb::kDefaultColumnFamilyName, rocksdb::ColumnFamilyOptions()));
	}
	status = rocksdb::DB::Open(storage->options, db_path, column_families, &handles, &db);
    assert(status.ok());
	for (const auto & entry : handles){
		tables[entry->GetName()] = new CTable(db, entry);
		std::cout << name << ": Loading '" << entry->GetName() << "'" << std::endl;
	}
}
CTable* CDatabase::table_create(std::string table_name){
	rocksdb::Status status;
	rocksdb::ColumnFamilyHandle* handle;
	if(tables.find(table_name) != tables.end()){
		return nullptr;
	}
	status = db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), table_name, &handle);
	if(status.ok()){
		return tables[handle->GetName()] = new CTable(db, handle);
	}
	return nullptr;
}
bool CDatabase::table_drop(std::string table_name){
	//rocksdb::Status status;
	//CTable* table = table_get(table_name);
	//if(!table_get(table_name)) return false;
	//db->DropColumnFamily()
	return false;
}
CDatabase::~CDatabase(){
	for (auto &entry : tables) // access by reference to avoid copying
	{
		db->DestroyColumnFamilyHandle(entry.second->getHandle());
		delete entry.second;
	}
	tables.clear();
    rocksdb::Status status = db->Close();
    assert(status.ok());
}
/*

	rocksdb::Status status = rocksdb::DB::Open(options, path, &db);
	assert(status.ok());
	status = db->Put(rocksdb::WriteOptions(), "key1", "valeur de test");
	assert(status.ok());

	std::string gettedVal;
	status = db->Get(rocksdb::ReadOptions(), "key1", &gettedVal);
	assert(status.ok());
	std::cout << "Key1: " << gettedVal << std::endl;

	status = db->Close();
	assert(status.ok());
}
*/