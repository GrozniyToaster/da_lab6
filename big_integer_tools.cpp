#include "big_integer_tools.hpp"

namespace NBigInt{
    int64_t StrToll( const TVectorWatcher<std::basic_string, char>& segment){
        int64_t res = 0;
        for (int i = 0; i < segment.Size(); ++i){
            res *= 10;
            res += static_cast<int64_t>(segment[i] - '0');
        }
        return res;
    }
    uint ClosestPower2( uint a ){
        while ( a & (a - 1) ){
            ++a;
        }
        return a;
    }
}