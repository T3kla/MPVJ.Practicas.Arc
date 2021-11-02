#include "time.h"
#include <iostream>
#include <profileapi.h>

namespace mytime
{

LARGE_INTEGER time_old;

long long int DeltaTime()
{
    LARGE_INTEGER time_new;
    QueryPerformanceCounter(&time_new);
    time_new.auto delta = time_new - time_old;
    time_old = time_new;
    return delta.count();
}

}; // namespace mytime
