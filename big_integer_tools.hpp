#pragma once
#include <iostream>

namespace NBigInt{
    template<template <typename, typename... > class Container, typename Type>
    class TSpan{
    public:
        const Container<Type>& v;
        const int begin = 0, end = v.size();

        TSpan() = delete;
        template<template <typename> class OC, typename OT>
        TSpan(TSpan<OC,OT> ) = delete;
        template<template <typename> class OC, typename OT>
        TSpan(TSpan<OC,OT>&& ) = delete;

        TSpan(const Container<Type>& v ): v(v){}
        TSpan(const Container<Type>& v, int start, int end ): v(v), begin(start), end(end) {}

        ~TSpan() = default;

        TSpan& operator=(TSpan& ) = delete;
        TSpan& operator=(TSpan&& rhs) = delete;
        inline const Type& operator[]( size_t pos ) const noexcept { return this->v[begin + pos]; }
        inline int Size() const noexcept { return (this->end - this->begin); }
    };

    int64_t StrToll( const TSpan<std::basic_string, char>& segment);
    uint ClosestPower2( uint a );
}

