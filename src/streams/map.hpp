#ifndef STREAM_MAP_HPP
#define STREAM_MAP_HPP

#include "defines.hpp"
#include "map.hpp"

STREAMS_NS

template<typename T, typename F>
class map
{
public:
    template<typename I>
    class iter
    {
    public:
        iter(I i, F f) :
            i(i),
            f(f) {}

        auto operator*() const
        {
            return f(*i);
        }

        auto& operator++()
        {
            ++i;
            return *this;
        }

        bool operator==(const iter<I>& other)
        {
            return i == other.i;
        }

        bool operator!=(const iter<I>& other)
        {
            return !(*this == other);
        }

    private:
        I i;
        F f;
    };

    map(T input, F f) :
        input(input),
        f(f) {}

    auto begin() const
    {
        return iter<decltype(input.begin())>(input.begin(), f);
    }

    auto end() const
    {
        return iter<decltype(input.end())>(input.end(), f);
    }

private:
    T input;
    F f;
};

STREAMS_NS_END

#endif //STREAM_MAP_HPP
