#pragma once
#include <chrono>
namespace CoW
{
class timer
{
public:
    timer(long& duration) : _duration(duration)
    {
        _startTime = std::chrono::high_resolution_clock::now();
    }
    ~timer()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds duration = endTime - _startTime;
        _duration = duration.count();
    }

private:
    long& _duration;
    std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;    
};
}