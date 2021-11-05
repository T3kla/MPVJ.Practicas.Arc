#pragma once
#include <windows.h>

namespace tkl
{

struct counter
{
    LARGE_INTEGER buffer;
    double freq = 0.0;
    long long anchor = 0;
    void stamp();
    double measure();
};

}; // namespace tkl
