#ifndef __CPP_HACK_DEFER_H_INCLUDED__
#define __CPP_HACK_DEFER_H_INCLUDED__

#include <utility>

namespace defer_ns {
    class helper {
    public:
        template <typename Callable>
        class helper_impl {
        public:
            helper_impl(Callable c) : call_(c) {}
            ~helper_impl() { call_(); }
            helper_impl(helper_impl&& o) : call_(std::move(o.call_)) {}
        private:
            Callable call_;
        };

        template <typename Callable>
        helper_impl<Callable> operator<<(Callable c) { return c; }
    };
}

#if defined(__GNUC__) || defined(__clang__)
#define _DEFER_UNUSED_ATTRIBUTE_ [[gnu::unused]]
#else
#define _DEFER_UNUSED_ATTRIBUTE_ [[maybe_unused]]
#endif

#define _defer_concat_macro_hack2(a, b) a ## b
#define _defer_concat_macro_hack1(a, b) _defer_concat_macro_hack2(a, b)
#define defer \
    _DEFER_UNUSED_ATTRIBUTE_ const auto& _defer_concat_macro_hack1(__defer_autoval_for_line_, __LINE__) = defer_ns::helper() << [&]()

#endif
