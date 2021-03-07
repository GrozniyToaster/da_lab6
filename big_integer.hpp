#pragma once

#include <iostream> 
#include <vector>
#include <cmath>
#include <iomanip>
#include "big_integer_tools.hpp"
//#define EXCEPTION_OPT //if define enable throwing exception in diff, div etc (uncomment to on)

namespace NBigInt{

class TBint{
  private:  
    static const int BASE = 100;
    static const int RADIX = 2;
    static const int KARATSUBA_NUMBER = 32; // the number of digits from which the Karatsuba algorithm begins to work
    std::vector<int64_t> Data;

    void DeleteLeadingZeroes() noexcept;

    static TBint ChooseVersionOfMul(const TBint& lhs, const TBint& rhs);
    static std::vector<int64_t> NaiveMul(const TSpan <std::vector, int64_t> &rhs, const TSpan <std::vector, int64_t> &lhs);
    static std::vector<int64_t> KaratsubaMul(const TSpan <std::vector, int64_t> &x, const TSpan <std::vector, int64_t> &y);
    static void Finalize(std::vector<int64_t>& res);

    static TBint LongDivWay(const TBint& lhs, const TBint& rhs);
    static int64_t BinSearchHelper(const TBint& ost, const std::vector<TBint> &preCalculated);
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
    TBint& operator/=(const TBint& rhs);
    explicit operator std::string() const;

    friend TBint operator+(const TBint& lhs, const TBint& rhs);
    friend TBint operator-(const TBint& lhs, const TBint& rhs);
    friend TBint operator*(const TBint& lhs, const TBint& rhs);
    friend TBint operator/(const TBint& lhs, const TBint& rhs);
    friend std::istream& operator>>(std::istream& is, TBint& rhs);
    friend std::ostream& operator<<(std::ostream& os, const TBint& rhs);
    friend bool operator<( const TBint& lhs, const TBint& rhs );
    friend bool operator>( const TBint& lhs, const TBint& rhs );
    friend bool operator==( const TBint& lhs, const TBint& rhs );
    friend bool operator!=( const TBint& lhs, const TBint& rhs );
    friend bool operator<=( const TBint& lhs, const TBint& rhs );
    friend bool operator>=( const TBint& lhs, const TBint& rhs );
    friend TBint pow(TBint a, TBint n);
};

}