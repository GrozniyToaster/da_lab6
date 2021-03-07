#pragma once


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

    template <typename Iterator>
    int64_t StrToll( Iterator i, Iterator end){
        int64_t res = 0;
        while ( i != end ){
            res *= 10;
            res += static_cast<int64_t>(*i - '0');
            ++i;
        }
        return res;
    }

    inline uint ClosestPower2( uint a ){
        while ( a & (a - 1) ){
            ++a;
        }
        return a;
    }
}

