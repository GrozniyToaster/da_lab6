#pragma once

#include <iostream> 
#include <vector>
#include <cmath>
#include <iomanip>
#include "big_integer_tools.hpp"
//#define EXCEPTION_OPT //if define enable throwing exception in diff, div etc (uncomment to on)

namespace NBigInt {

    using TRType = int64_t;

    class TBint {
    private:
        static const int BASE = 1e6;
        static const int RADIX = 6;
        static const int KARATSUBA_NUMBER = 64; // the number of digits from which the Karatsuba algorithm begins to work
        std::vector<TRType> Data;

        void DeleteLeadingZeroes() noexcept;

        static TBint ChooseVersionOfMul(const TBint& lhs, const TBint& rhs);
        static std::vector<TRType> NaiveMul(const TSpan <std::vector, TRType>& rhs, const TSpan <std::vector, TRType>& lhs);
        static std::vector<TRType> KaratsubaMul(const TSpan <std::vector, TRType>& x, const TSpan <std::vector, TRType>& y);
        static void Finalize(std::vector<TRType>& res);

        static TBint LongDivWay(const TBint& lhs, const TBint& rhs);
        static TRType BinSearchHelper(const TBint& ost, const TBint& rhs);

    public:
        TBint() = default;
        TBint(const TBint& rhs) = default;
        TBint(TBint&& rhs) noexcept;
        explicit TBint(const std::string&);
        TBint(TRType);

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
        friend bool operator<(const TBint& lhs, const TBint& rhs);
        friend bool operator>(const TBint& lhs, const TBint& rhs);
        friend bool operator==(const TBint& lhs, const TBint& rhs);
        friend bool operator!=(const TBint& lhs, const TBint& rhs);
        friend bool operator<=(const TBint& lhs, const TBint& rhs);
        friend bool operator>=(const TBint& lhs, const TBint& rhs);
        friend TBint pow(TBint a, const TBint& n);
    };

}