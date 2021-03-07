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

    template<typename T>
    class TVectorWatcher{
    public:
        const std::vector<T>& v;
        const int begin = 0, end = v.size();

        TVectorWatcher() = delete;
        template<class U>
        TVectorWatcher( TVectorWatcher<U> ) = delete;
        template<class U>
        TVectorWatcher( TVectorWatcher<U>&& ) = delete;

        TVectorWatcher( const std::vector<T>& v ): v(v){}
        TVectorWatcher( const std::vector<T>& v, int start, int end ): v(v), begin(start), end(end) {}

        ~TVectorWatcher() = default;

        TVectorWatcher& operator=(TVectorWatcher& ) = delete;
        TVectorWatcher& operator=(TVectorWatcher&& rhs) = delete;
        inline const T& operator[]( size_t pos ) const noexcept { return this->v[begin + pos]; }
        inline int Size() const noexcept { return (this->end - this->begin); }
    };

class TBint{
  private:  
    static const int BASE = 100;
    static const int RADIX = 2;
    static const int KARATSUBA_NUMBER = 2; // the number of digits from which the Karatsuba algorithm begins to work
    std::vector<int64_t> Data;

    void DeleteLeadingZeroes() noexcept;

    static TBint ChooseVersionOfMul(const TBint& lhs, const TBint& rhs);
    static std::vector<int64_t> NaiveMul(const TVectorWatcher <int64_t> &rhs, const TVectorWatcher <int64_t> &lhs);
    static std::vector<int64_t> KaratsubaMul(const TVectorWatcher <int64_t> &x, const TVectorWatcher <int64_t> &y);
    static void Finalize(std::vector<int64_t>& res);

    static TBint LongDivWay(const TBint& lhs, const TBint& rhs);
    static int64_t BinSearchHelper(const TBint& ost, const std::vector<TBint> &preCalculated);
    static bool LessHelper(const std::vector<int64_t>& ost, const TBint& toCheck);
    static void DiffHelper(std::vector<int64_t>& ost, const TBint& diff);
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
    operator std::string() const;

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