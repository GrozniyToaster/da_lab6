#include "big_integer_tools.hpp"

namespace NBigInt {
    long long StrToll(const TSpan<std::basic_string, char>& segment) {
        long long res = 0;
        for (int i = 0; i < segment.Size(); ++i) {
            res *= 10;
            res += static_cast<long long>(segment[i] - '0');
        }
        return res;
    }
    uint ClosestPower2(uint a) {
        while (a & (a - 1)) {
            ++a;
        }
        return a;
    }
}