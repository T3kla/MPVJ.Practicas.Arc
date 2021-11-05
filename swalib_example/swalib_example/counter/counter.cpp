#include "counter.h"
#include <iostream>
#include <windows.h>

namespace tkl
{

void counter::stamp()
{
    if (!QueryPerformanceFrequency(&buffer))
        throw "counter error";

    freq = double(buffer.QuadPart) / 1000.0;
    QueryPerformanceCounter(&buffer);
    anchor = buffer.QuadPart;
}

double counter::measure()
{
    QueryPerformanceCounter(&buffer);
    return double(buffer.QuadPart - anchor) / freq;
}

}; // namespace tkl
