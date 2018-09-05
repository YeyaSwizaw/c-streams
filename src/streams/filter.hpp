#ifndef STREAM_FILTER_HPP
#define STREAM_FILTER_HPP

#include "defines.hpp"
#include "filter.hpp"

STREAMS_NS

template<typename T, typename F>
class filter
{
public:
    template<typename I>
    class iter
    {
    public:
        iter(I i, F f, I end) :
            i(i),
            end(end),
            f(f) {}

        auto operator*() const
        {
            return *i;
        }

        auto& operator++()
        {
            do
            {
                ++i;
            } while(i != end && !f(*i));

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
        I i, end;
        F f;
    };

    filter(T input, F f) :
        input(input),
        f(f) {}

    auto begin() const
    {
        return iter<decltype(input.begin())>(input.begin(), f, input.end());
    }

    auto end() const
    {
        return iter<decltype(input.end())>(input.end(), f, input.end());
    }

private:
    T input;
    F f;
};

STREAMS_NS_END

#endif //STREAM_FILTER_HPP
