#ifndef STREAM_FILTER_HPP
#define STREAM_FILTER_HPP

#include "defines.hpp"
#include "iterable.hpp"
#include "iter_base.hpp"

STREAMS_NS

template<typename Iter, typename F>
class filter_iter final : public iter_base<Iter, filter_iter<Iter, F>> {
public:
    using value_type = typename Iter::value_type;

    filter_iter(Iter from, Iter to, F f) :
            iter_base(std::move(from), std::move(to)),
            f(std::move(f)) {}

    const value_type& operator*() const
    {
        return *this->inner;
    }

    auto& operator++()
    {
        do
        {
            ++this->inner;
        } while(this->inner != this->end && !f(*this->inner));

        return *this;
    }

private:
    F f;
};

template<typename Inner, typename F>
using filter = iterable<Inner, filter_iter<decltype(std::declval<Inner>().begin()), F>, F>;

STREAMS_NS_END

#endif //STREAM_FILTER_HPP
