#if defined(PULL_IN_STL)
#include <sstream>
#include <string>
#endif

#include "defer.hpp"

#define FMT_HEADER_ONLY
#define FMT_USE_NOEXCEPT 1
#define FMT_USE_USER_DEFINED_LITERALS 0
#include "../fmt/format.h"

#define out fmt::print

struct S_type {
    int x = 1;
    int y = 2;
    int z = 3;
};

static inline void format_arg(fmt::BasicFormatter<char> &f, const char *&, const S_type& s)
{
    f.writer().write("{{{}, {}, {}}}", s.x, s.y, s.z);
}

int main()
{
    void *p = std::malloc(1024);
    long l = 0x0102030405l;
    S_type s;

#if defined(PULL_IN_STL)
    std::stringstream ss;
    ss << "This is a (" << l << ") test";
    out("{}\n", ss.str());
#endif

    defer {
        out("> p = {:0<16p}\n> s = {}\n", p, s);
        out("> Done with program\n");
    };

    defer {
        out("> SECOND top-level defer\n");
    };

    {
        defer {
            std::free(p);
            p = nullptr;
            out(">>> l = {:x}\n", l);
            out(">>> Done with scope\n");
        };

        out(">>\n");
        out(">> In scope\n");
        out(">>\n");
    }

    out("\n");
    out("Main program\n");
    out("\n");

    return 0;
}
