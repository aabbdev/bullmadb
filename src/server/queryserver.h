#ifndef __QUERYSERVER_H__
#define __QUERYSERVER_H__
#include <atomic>

class QueryServer
{
public:
    QueryServer();
    ~QueryServer();
    void Start();
    void Stop();
private:
    std::atomic<uint64_t> counter;
};
#endif // __QUERYSERVER_H__