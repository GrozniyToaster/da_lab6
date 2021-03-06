#pragma once

#include <iostream> 
#include <vector>
#include <cmath>
#include <iterator>
#include <iomanip>

#define EXCEPTION_OPT //if define enable throwing exception in diff div etc (comment to off)

namespace NBigInt{
    template <typename Iterator>
    int64_t StrToll( Iterator i, Iterator end);

    uint ClosestPower2( uint a );

class TBint{
  private:  
    static const int BASE = 100;
    static const int RADIX = 2;
    static const int KARATSUBA_NUMBER = 128; // the number of digits from which the Karatsuba algorithm begins to work
    std::vector<int64_t> Data;

    void DeleteLeadingZeroes() noexcept;
    static std::vector<int64_t> NaiveMul(const std::vector<int64_t>& rhs, const std::vector<int64_t>& lhs);
    static std::vector<int64_t> KaratsubaMul(const std::vector<int64_t>& x, const std::vector<int64_t>& y);
    static void Finalize(std::vector<int64_t>& res);
  public:
    TBint() = default;
    TBint(const TBint& rhs) = default;
    TBint(TBint&& rhs) noexcept;
    explicit TBint(const std::string&);
    TBint(int64_t);

    ~TBint() = default;

    TBint& operator=(const TBint& rhs) = default;
    TBint& operator=(TBint&& rhs) noexcept;
    TBint& operator+=(const TBint& rhs);
    TBint& operator-=(const TBint& rhs);
    TBint& operator*=(const TBint& rhs);
    operator std::string() const;

    friend TBint operator+( const TBint& lhs, const TBint& rhs);
    friend TBint operator-( const TBint& lhs, const TBint& rhs);
    friend TBint operator*( const TBint& lhs, const TBint& rhs);
    friend std::istream& operator>>(std::istream& is, TBint& rhs);
    friend std::ostream& operator<<(std::ostream& os, const TBint& rhs);
    friend bool operator<( const TBint& lhs, const TBint& rhs );
    friend bool operator>( const TBint& lhs, const TBint& rhs );
    friend bool operator==( const TBint& lhs, const TBint& rhs );
    friend bool operator!=( const TBint& lhs, const TBint& rhs );
    friend bool operator<=( const TBint& lhs, const TBint& rhs );
    friend bool operator>=( const TBint& lhs, const TBint& rhs );

};

//using bint_t = uint64_t;
    using bint_t = TBint;

//TODO переписать через указатель и индексы
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
}