#include <vector>
#include <string>
#include <iostream>

#include "streams/streams.hpp"

int main()
{
    std::vector<int> v{0, 1, 2, 3};

    for(const auto& i : streams::stream(v)
        .filter([](int i) { return i % 2 == 0; })
        .map([](int i) { return "#" + std::to_string(i); }))
    {
        std::cout << i << std::endl;
    }

    return EXIT_SUCCESS;
}
