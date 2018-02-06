#ifndef __CPP_HACK_DEFER_H_INCLUDED__
#define __CPP_HACK_DEFER_H_INCLUDED__

namespace defer_ns {
    class helper {
    public:
        template <typename Callable>
        class helper_impl {
        public:
            helper_impl(Callable c) : call_(c) {}
            ~helper_impl() { call_(); }
        private:
            Callable call_;
        };

        template <typename Callable>
        helper_impl<Callable> operator<<(Callable c) { return c; }
    };
}

#if defined(__GNUC__) || defined(__clang__)
#define _DEFERHACK_UNUSED_ATTR_DEF_ [[gnu::unused]]
#else
#define _DEFERHACK_UNUSED_ATTR_DEF_ [[maybe_unused]]
#endif

#define _deferhack_cathack_2(a, b) a ## b
#define _deferhack_cathack_1(a, b) _deferhack_cathack_2(a, b)
#define defer \
    _DEFERHACK_UNUSED_ATTR_DEF_ \
    const auto& _deferhack_cathack_1(_deferhack_val_for_line_, __LINE__) = \
        defer_ns::helper() << [&]()

#endif  /* __CPP_HACK_DEFER_H_INCLUDED__ */
