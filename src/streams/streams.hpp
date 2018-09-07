#ifndef STREAM_STREAMS_HPP
#define STREAM_STREAMS_HPP

#include "defines.hpp"
#include "iterable.hpp"
#include "map.hpp"
#include "filter.hpp"

STREAMS_NS

template<typename T>
class stream_t
{
public:
    using value_type = typename T::value_type;
    using iterator = typename T::iterator;

    stream_t(T input) :
        input(input) {}

    template<typename F>
    auto map(F f) const
    {
        using map_t = ::STREAMS_NS_NAME::map<T, F>;
        return stream_t<map_t>(map_t(std::move(input), std::move(f)));
    }

    template<typename F>
    auto filter(F f) const
    {
        using filter_t = ::STREAMS_NS_NAME::filter<T, F>;
        return stream_t<filter_t>(filter_t(std::move(input), std::move(f)));
    }

    iterator begin() const
    {
        return input.begin();
    }

    iterator end() const
    {
        return input.end();
    }

private:
    T input;
};

template<typename I>
struct iter_wrapper
{
    using value_type = typename I::value_type;
    using iterator = I;

    auto begin() const
    {
        return b;
    }

    auto end() const
    {
        return e;
    }

    I b, e;
};

template<typename T>
auto stream(const T& input)
{
    using wrapper_t = iter_wrapper<decltype(input.begin())>;
    return stream_t<wrapper_t>(wrapper_t{input.begin(), input.end()});
}

STREAMS_NS_END

#endif //STREAM_STREAMS_HPP
