#ifndef STREAM_FILTER_HPP
#define STREAM_FILTER_HPP

#include "defines.hpp"
#include "iterable.hpp"

STREAMS_NS

template<typename Iter, typename F>
class filter_iter
{
public:
    filter_iter(Iter from, Iter to, F f) :
            inner(std::move(from)),
            end(std::move(to)),
            f(std::move(f)) {}

    auto operator*() const
    {
        return *inner;
    }

    auto& operator++()
    {
        do
        {
            ++inner;
        } while(inner != end && !f(*inner));

        return *this;
    }

    bool operator==(const filter_iter<Iter, F>& other)
    {
        return inner == other.inner;
    }

    bool operator!=(const filter_iter<Iter, F>& other)
    {
        return !(*this == other);
    }

private:
    Iter inner, end;
    F f;
};

template<typename Inner, typename F>
using filter = iterable<Inner, filter_iter<decltype(std::declval<Inner>().begin()), F>, F>;

STREAMS_NS_END

#endif //STREAM_FILTER_HPP
