#ifndef CSNOWFLAKE_H_
#define CSNOWFLAKE_H_

#include <sys/time.h>

#include <iostream>
#include <mutex>
#include <string>
#include <assert.h>
/*
16 bit - db id
16 bit - table id
64 bit - timestamp
32 bit - rng
*/
namespace util {
    class CSnowflake
    {
    public:
        static uint64_t GetTimeStamp() {
            struct timeval tv;
            gettimeofday(&tv,NULL);
            return (tv.tv_sec * 1000) + tv.tv_usec/1000;
        }
    private:
        const static uint64_t GENESIS       =   1480166465631;
        const static uint64_t MAX_TIMESTAMP =   ((uint64_t)1<<34) - 1;
        const static uint16_t MAX_SHARDS    =   (1<<16) - 1;
        const static uint16_t MAX_SEQUENCE  =   (1<<14) - 1;


        uint64_t shard_id;
        uint64_t sequence;
        uint64_t lastStmp;

        std::mutex mutex_;
        uint64_t getNextMill()
        {
            uint64_t mill = GetTimeStamp();
            while (mill <= lastStmp)
            {
                mill = GetTimeStamp();
            }
            return mill;
        }

    public:
        CSnowflake(uint16_t shard_id)
        {
            assert(!((uint64_t)shard_id > MAX_SHARDS || shard_id < 0));
        }
        ~CSnowflake()
        {
        }
        uint64_t Generate()
        {
            std::unique_lock<std::mutex> lock(mutex_);
            uint64_t currStmp = GetTimeStamp();
            if (currStmp < lastStmp)
            {
                std::cout << "Clock moved backwards.  Refusing to generate id" << std::endl;
                exit(0);
            }

            if (currStmp == lastStmp)
            {
                sequence = (sequence + 1) & MAX_SEQUENCE;
                if (sequence == 0)
                {
                    currStmp = getNextMill();
                }
            }
            else
            {
                sequence = 0;
            }
            lastStmp = currStmp;
            union { // Snowflake bitfield builder
                struct {
                    uint16_t sequence : 14;
                    uint16_t shard_id : 16;
                    uint64_t timestamp : 34;
                };
                uint64_t unique_id;
            } sfk;
            sfk.timestamp = (currStmp - GENESIS); // start_stmp_
            sfk.shard_id = shard_id;
            sfk.sequence = sequence;
            return sfk.unique_id;
        }
    };
};
#endif // CSNOWFLAKE_H_