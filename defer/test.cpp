#include <cstdio>
#include <cstdlib>
#include "defer.hpp"

#define out(fmt, ...) std::printf("[%3d] " fmt "\n", __LINE__, ##__VA_ARGS__)

struct S_type {
    int x = 1;
    int y = 2;
    int z = 3;
};

int main()
{
    void *p = std::malloc(1024);
    [[gnu::unused]] long l = 0x0102030405l;
    [[gnu::unused]] S_type s;

    defer {
        out("> p = %p", p);
        out("> s = {%d, %d, %d}", s.x, s.y, s.z);
        out("> Done with program");
    };

    defer {
        out("> SECOND top-level defer");
    };

    out("%zd", sizeof(_deferhack_val_for_line_19));

    {
        defer {
            std::free(p);
            p = nullptr;
            out(">>> l = %lx", l);
            out(">>> Done with scope");
        };

        out(">>");
        out(">> In scope");
        out(">>");
    }

    out("");
    out("Main program");
    out("");

    return 0;
}
