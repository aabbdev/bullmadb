# Install dependencies
sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev
mkdir -p third_party
git submodule update --recursive

# Builf dependencies
## Msgpack
cd third_party/msgpack
cmake -DMSGPACK_CXX17=ON .
make
## Google Marl
cd ../marl
git submodule update --init
mkdir -p build
cd build
cmake .. -DMARL_BUILD_EXAMPLES=1 -DMARL_BUILD_TESTS=1
make
## XXHASH
cd ../../xxhash
make
## RocksDB
cd ../rocksdb
USE_SSE=1 make static_lib