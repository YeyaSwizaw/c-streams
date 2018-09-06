#ifndef STREAM_MAP_HPP
#define STREAM_MAP_HPP

#include "defines.hpp"
#include "iterable.hpp"

STREAMS_NS

template<typename Iter, typename F>
class map_iter
{
public:
    map_iter(Iter from, Iter to, F f) :
        inner(std::move(from)),
        f(std::move(f)) {}

    auto operator*() const
    {
        return f(*inner);
    }

    auto& operator++()
    {
        ++inner;
        return *this;
    }

    bool operator==(const map_iter<Iter, F>& other)
    {
        return inner == other.inner;
    }

    bool operator!=(const map_iter<Iter, F>& other)
    {
        return !(*this == other);
    }

private:
    Iter inner;
    F f;
};

template<typename Inner, typename F>
using map = iterable<Inner, map_iter<decltype(std::declval<Inner>().begin()), F>, F>;

STREAMS_NS_END

#endif //STREAM_MAP_HPP
