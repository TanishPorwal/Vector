#pragma once

#include <iostream>
#include <chrono>

struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    Timer() : duration(0)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    float getCurrentTime()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        return duration.count();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        if(duration.count() < 1000) std::cout << duration.count() * 1000 << "ms\n";
        else std::cout << duration.count() << "s\n";
    }
};