#ifndef PACK_H
#define PACK_H
#include <type_traits>


namespace pack_detail {


    template <typename... Args>
    constexpr int packSize = sizeof...(Args);

    template <int QueryIndex, typename... Args> 
    struct _packIndexToType {
        static_assert(QueryIndex >= 0, "Index must be positive");
        static_assert(QueryIndex < sizeof...(Args), "Index out of range");
    };

    template <int QueryIndex, typename U, typename ... Args> 
    struct _packIndexToType<QueryIndex, U, Args...> {
        using type = typename  _packIndexToType<QueryIndex - 1, Args...>::type;
    };

    template <typename U, typename... Args> 
    struct _packIndexToType<0, U, Args...> {
        using type = U;
    };

    template <int QueryIndex, typename... Args> using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

    // empty pack
    template <int Accumulated, typename QueryType, typename... Args>
    constexpr int _packTypeToIndex = -1;

    template <int Accumulated, typename QueryType, typename U, typename... Args>
    constexpr int _packTypeToIndex<Accumulated, QueryType, U, Args...> = std::is_same_v<QueryType, U>
                                                                                                ? Accumulated 
                                                                                                : _packTypeToIndex<Accumulated + 1, QueryType, Args...>;

                                                                                                template <typename QueryType, typename... Args>

    constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

};


template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    static constexpr int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};




#endif  // PACK_H
