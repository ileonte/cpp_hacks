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

#define defer [[gnu::unused]] const auto& _local_defer__ ## __LINE__ = defer_ns::helper() << [&]()

#endif
