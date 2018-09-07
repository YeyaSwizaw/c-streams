#ifndef STREAM_ITERABLE_HPP
#define STREAM_ITERABLE_HPP

#include "defines.hpp"

#include <tuple>

STREAMS_NS

template<typename Inner, typename Iter, typename... Args>
class iterable
{
public:
    using value_type = typename Iter::value_type;
    using iterator = typename Iter;

    iterable(Inner inner, Args... args) :
        inner(std::move(inner)),
        args(std::make_tuple(std::move(args)...)) {}

    iterator begin() const
    {
        return std::apply([this](Args... args) { return Iter(inner.begin(), inner.end(), std::move(args)...); }, std::move(args));
    }

    iterator end() const
    {
        return std::apply([this](Args... args) { return Iter(inner.end(), inner.end(), std::move(args)...); }, std::move(args));
    }

private:
    Inner inner;
    std::tuple<Args...> args;
};

STREAMS_NS_END

#endif //STREAM_ITERABLE_HPP
