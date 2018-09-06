#ifndef STREAM_ITER_BASE_HPP
#define STREAM_ITER_BASE_HPP

#include "defines.hpp"

STREAMS_NS

template<typename Iter, typename CRTP>
class iter_base {
public:
    iter_base(Iter from, Iter to) :
        inner(std::move(from)),
        end(std::move(to)) {}

    bool operator==(const CRTP& other)
    {
        return inner == other.inner;
    }

    bool operator!=(const CRTP& other)
    {
        return !(*this == other);
    }

protected:
    Iter inner, end;
};

STREAMS_NS_END

#endif //STREAM_ITER_BASE_HPP
