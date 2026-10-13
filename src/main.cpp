#include "pack.h"

int main() { 

    using P = Pack<int, float, char, int, double>;

    static_assert(P::size == 5);

    static_assert(std::is_same_v<P::type<0>, int>);
    static_assert(std::is_same_v<P::type<1>, float>);
    static_assert(std::is_same_v<P::type<2>, char>);

    static_assert(P::index<int> == 0);
    static_assert(P::index<char> == 2);
    static_assert(P::index<double> == 4);
    static_assert(P::index<size_t> == -1);


    return 0;
}
