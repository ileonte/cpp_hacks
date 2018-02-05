#include <cstdio>
#include "defer.hpp"

int main()
{
    defer { std::printf("Done with program\n"); };

    {
        defer { std::printf("Done with scope\n"); };
        std::printf("In scope\n");
    }

    return 0;
}
