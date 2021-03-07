// Your First C++ Program

#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

#include "db/storage.h"

#include <marl/defer.h>
#include <marl/scheduler.h>
#include <marl/waitgroup.h>

/*
auto MINIMAL_DURABILITY = rocksdb::WriteOptions();
MINIMAL_DURABILITY.disableWAL = true;
MINIMAL_DURABILITY.sync = false;

auto SOFT_DURABILITY = rocksdb::WriteOptions();
SOFT_DURABILITY.disableWAL = false;
SOFT_DURABILITY.sync = false;

auto HARD_DURABILITY = rocksdb::WriteOptions();
HARD_DURABILITY.disableWAL = false;
HARD_DURABILITY.sync = true;
*/
int main( int argc, const char* argv[] ) {
    //std::cout << "Hello World!" <<std::endl;
    CStorage* storage = new CStorage("chakradb_data");

    delete storage;
    return 0;
}