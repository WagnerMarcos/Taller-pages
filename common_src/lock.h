#ifndef LOCK__T
#define LOCK__T

#include <mutex>

class Lock{
public:
    explicit Lock(std::mutex &m) : m(m){
        m.lock();
    }
    ~Lock(){
        m.unlock();
    }
private:
    std::mutex& m;
    Lock(const Lock&)=delete;
    Lock& operator=(const Lock&)=delete;
    Lock(Lock&&)=delete;
    Lock& operator=(Lock&&)=delete;
};

#endif
