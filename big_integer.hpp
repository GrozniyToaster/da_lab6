#pragma once

#include <iostream> 
#include <vector>
#include <cmath>
#include <iterator>
#include <iomanip>

namespace NBigInt{

class TBint{
  private:  
    static const int Base = 10;
    static const int Radix = 1;
    std::vector<int64_t> Data;
  public:
    TBint() = default;
    TBint(std::string&);
    TBint(uint64_t);


    ~TBint() = default;


    TBint& operator+=(const TBint& rhs);
    TBint& operator-=(const TBint& rhs);



    friend TBint operator+( const TBint& lhs, const TBint& rhs);
    friend std::istream& operator>>(std::istream& is, TBint& rhs);
    friend std::ostream& operator<<(std::ostream& os,const TBint& rhs);
};

//using bint_t = uint64_t;
    using bint_t = TBint;
}