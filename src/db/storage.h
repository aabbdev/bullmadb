#ifndef CSTORAGE_H_
#define CSTORAGE_H_

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <filesystem>
#include <msgpack.hpp>
#include <rocksdb/db.h>

#include "database.h"

namespace fs = std::filesystem;

class CStorage
{
// public variables and functions
public:
	// class constructor
	CStorage(std::string);
	~CStorage();
	std::vector<CDatabase*> databases;
	rocksdb::Options options;
	rocksdb::WriteOptions MINIMAL_DURABILITY;
	rocksdb::WriteOptions SOFT_DURABILITY;
	rocksdb::WriteOptions HARD_DURABILITY;
	static CStorage* getInstance();
protected:
	static CStorage* singleton;
};
#endif // CSTORAGE_H_