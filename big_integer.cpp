#include "big_integer.hpp"

namespace NBigInt {

 /*
    TBint &TBint::operator+=(const TBint &rhs) {
        int tSize = this->Data.size(), rSize = rhs.Data.size();
        bool isThisMin = tSize <= rSize;
        int m;

        if (isThisMin){
            m = tSize;
        } else {
            m = rSize;
        }
//TODO проверить что количество цифр в бейс позволяет избежать переполнения
        bool isOverflow = false;
        for (int i = 0; i < m; ++i) {
            this->Data[i] += rhs.Data[i];
            this->Data[i] += isOverflow;
            isOverflow = Data[i] >= this->Base;
            if (isOverflow){
                this->Data[i] -= this->Base;
            }
        }

        if ( tSize == rSize ){
            if ( isOverflow  ){
                this->Data.push_back(1);
            }
            return *this;
        }


        if ( ! isThisMin ) return *this;
        for ( int i = m; i < rSize; ++i ){
            this->Data.push_back(rhs.Data[i]);
        }
        return *this;
    }
    */

    TBint operator+(const TBint &lhs, const TBint &rhs) {
        TBint res;
        size_t lSize = lhs.Data.size(), rSize = rhs.Data.size();
        int m = std::max( lSize, rSize );
        res.Data.resize(m);
        int64_t overflow = 0;
        for ( int i = 0; i < m; ++i ){
            uint64_t summ = overflow;
            if ( i < lSize ){
                summ += lhs.Data[i];
            }
            if ( i < rSize ){
                summ += rhs.Data[i];
            }
            overflow = summ / TBint::Base;
            res.Data[i] = summ % TBint::Base;
        }
        if (overflow) {
            res.Data.push_back(overflow);
        }

        return res;
    }

    std::istream& operator>>( std::istream& is, TBint& rhs ){
        std::string tmp;
        is >> tmp;
        TBint newBInt(tmp);
        rhs.Data.swap(newBInt.Data);
        return is;
    }

    TBint::TBint(std::string& str) {
        int newSize = ceil( static_cast<double> (str.size()) / TBint::Radix );
        this->Data.resize(newSize);
        //TODO check borders
        for (size_t i = 0; i < str.size(); ++i) {
            this->Data[str.size() - i - 1] = static_cast<int64_t>(str[i] - '0');
        }
    }

    std::ostream& operator<<(std::ostream &os, const TBint& rhs) {
        os << rhs.Data.back();
        os << std::setfill('0') << std::setw(TBint::Radix);
        std::copy( rhs.Data.rbegin() + 1 , rhs.Data.rend(), std::ostream_iterator<uint64_t>( os ));
        return os;
    }


}
