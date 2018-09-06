#ifndef STREAM_MAP_HPP
#define STREAM_MAP_HPP

#include "defines.hpp"
#include "iterable.hpp"
#include "iter_base.hpp"

STREAMS_NS

template<typename Iter, typename F>
class map_iter final : public iter_base<Iter, map_iter<Iter, F>>
{
public:
    map_iter(Iter from, Iter to, F f) :
        iter_base(std::move(from), std::move(to)),
        f(std::move(f)) {}

    auto operator*() const
    {
        return f(*this->inner);
    }

    auto& operator++()
    {
        ++this->inner;
        return *this;
    }

private:
    F f;
};

template<typename Inner, typename F>
using map = iterable<Inner, map_iter<decltype(std::declval<Inner>().begin()), F>, F>;

STREAMS_NS_END

#endif //STREAM_MAP_HPP
