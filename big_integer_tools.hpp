#pragma once
#include <iostream>

namespace NBigInt{
    template<template <typename, typename... > class Container, typename Type>
    class TVectorWatcher{
    public:
        const Container<Type>& v;
        const int begin = 0, end = v.size();

        TVectorWatcher() = delete;
        template<template <typename> class OC, typename OT>
        TVectorWatcher( TVectorWatcher<OC,OT> ) = delete;
        template<template <typename> class OC, typename OT>
        TVectorWatcher( TVectorWatcher<OC,OT>&& ) = delete;

        TVectorWatcher( const Container<Type>& v ): v(v){}
        TVectorWatcher( const Container<Type>& v, int start, int end ): v(v), begin(start), end(end) {}

        ~TVectorWatcher() = default;

        TVectorWatcher& operator=(TVectorWatcher& ) = delete;
        TVectorWatcher& operator=(TVectorWatcher&& rhs) = delete;
        inline const Type& operator[]( size_t pos ) const noexcept { return this->v[begin + pos]; }
        inline int Size() const noexcept { return (this->end - this->begin); }
    };

    int64_t StrToll( const TVectorWatcher<std::basic_string, char>& segment);

    uint ClosestPower2( uint a );
}

