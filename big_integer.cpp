#include "big_integer.hpp"

namespace NBigInt {

    TBint::TBint(int64_t a) {
        if (a < TBint::Base) {
            if (a != 0) {
                this->Data.push_back(a);
            }
            return;
        }
        do {
            this->Data.push_back(a % TBint::Base);
            a /= TBint::Base;
        } while (a > 0);
        this->DeleteLeadingZeroes();
    }

    TBint::TBint(const std::string &str) {
        int newSize = ceil(static_cast<double> (str.size()) / TBint::Radix);
        this->Data.resize(newSize);
        auto i = str.rbegin();
        int d = 0;
        for (auto next = i + TBint::Radix; i < str.rend(); d++, i = next, next = i + TBint::Radix) {
            auto border = (next >= str.rend()) ? str.rend() : next;
            this->Data[d] = StrToll(border.base(), i.base());
        }
        this->DeleteLeadingZeroes();
    }

    void TBint::DeleteLeadingZeroes() noexcept {
        while (!this->Data.empty() && this->Data.back() == 0) {
            this->Data.pop_back();
        }
    }

    TBint &TBint::operator+=(const TBint &rhs) {
        size_t lSize = this->Data.size(), rSize = rhs.Data.size();
        int m = std::max(lSize, rSize);
        this->Data.resize(m, 0);
        int64_t overflow = 0;
        for (int i = 0; i < m; ++i) {
            this->Data[i] += overflow;
            if (i < rSize) {
                this->Data[i] += rhs.Data[i];
            }
            //TODO смотреть на что не переполняется в отрицательное
            overflow = this->Data[i] / TBint::Base;
            this->Data[i] = this->Data[i] % TBint::Base;
        }
        if (overflow) {
            this->Data.push_back(overflow);
        }
        return *this;
    }

    TBint operator+(const TBint &lhs, const TBint &rhs) {
        TBint res = lhs;
        res += rhs;
        return res;
    }

    //TODO чекуть лицом наличие с++17 и написать output_iterator
    std::istream &operator>>(std::istream &is, TBint &rhs) {
        std::string tmp;
        if (!(is >> tmp)) {
            return is;
        }
        TBint newBInt(tmp);
        rhs.Data.swap(newBInt.Data);
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const TBint &rhs) {
        if (rhs.Data.empty()) {
            os << '0';
            return os;
        }
        os << rhs.Data.back();
        os << std::setfill('0') << std::setw(TBint::Radix);
        std::copy(rhs.Data.rbegin() + 1, rhs.Data.rend(), std::ostream_iterator<int64_t>(os));
        os << std::resetiosflags(std::ios_base::basefield);
        return os;
    }

    TBint &TBint::operator-=(const TBint &rhs) {
#ifdef EXCEPTION_OPT
        if ( *this < rhs ){
            throw std::underflow_error("lhs less then rhs");
        }
#endif
        size_t lSize = this->Data.size(), rSize = rhs.Data.size();
        int m = std::max(lSize, rSize);
        this->Data.resize(m + 1, 0);
        int64_t underflow = 0;
        for (int i = 0; i < m; ++i) {
            this->Data[i] -= underflow;
            underflow = 0;
            if (i < rSize) {
                this->Data[i] -= rhs.Data[i];
            }
            if (this->Data[i] < 0) {
                underflow = 1;
                this->Data[i] += TBint::Base;
            }
            this->Data[i] = this->Data[i] % TBint::Base;
        }
        this->DeleteLeadingZeroes();

        return *this;
    }

    TBint operator-(const TBint &lhs, const TBint &rhs) {
        TBint res = lhs;
        res -= rhs;
        return res;
    }

    bool operator<(const TBint &lhs, const TBint &rhs) {
        if (lhs.Data.size() != rhs.Data.size()) {
            return lhs.Data.size() < rhs.Data.size();
        }
        for (int i = lhs.Data.size() - 1; i > 0; --i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] < rhs.Data[i];
            }
        }
        return false;
    }

    bool operator>(const TBint &lhs, const TBint &rhs) {
        if (lhs.Data.size() != rhs.Data.size()) {
            return lhs.Data.size() > rhs.Data.size();
        }
        for (int i = lhs.Data.size() - 1; i > 0; --i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] > rhs.Data[i];
            }
        }
        return false;
    }

    bool operator==(const TBint &lhs, const TBint &rhs) {
        if (lhs.Data.size() != rhs.Data.size()) {
            return false;
        }
        for (int i = 0; i < lhs.Data.size(); i++) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const TBint &lhs, const TBint &rhs) {
        return (!(lhs > rhs));
    }

    bool operator>=(const TBint &lhs, const TBint &rhs) {
        return (!(lhs < rhs));
    }

    TBint::operator std::string() const {
        if (this->Data.empty()) {
            return "0";
        }
        std::string res = std::to_string(this->Data.back());
        for (auto i = this->Data.size() - 2; i > 0; --i) {
            std::string tmp = std::to_string(this->Data[i]);
            int leadingZeroes = TBint::Radix - tmp.size();
            res.append(leadingZeroes, '0');
            res += tmp;
        }
        return res;
    }

    bool operator!=(const TBint &lhs, const TBint &rhs) {
        return !(lhs == rhs);
    }

    TBint::TBint(TBint &&rhs) noexcept {
        this->Data.swap(rhs.Data);
        this->DeleteLeadingZeroes();
    }

    TBint &TBint::operator=(TBint &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        this->Data.swap(rhs.Data);
        this->DeleteLeadingZeroes();
        return *this;
    }

    TBint &TBint::operator*=(const TBint &rhs) {
        TBint zero;
        if ( *this == zero || rhs == zero ){
            *this = std::move(zero);
            return *this;
        }
        TBint one (1);
        if (*this == one){
            *this = rhs;
            return *this;
        } else if ( rhs == one ){
            return *this;
        }
        size_t tSize = this->Data.size(), rSize = rhs.Data.size();
        std::vector<int64_t> res (tSize + rSize, 0);
        for (int i = 0; i < tSize; ++i){
            int64_t overflow = 0;
            for(int j = 0; j < rSize; ++j){
                res[i + j] += overflow + this->Data[i] * rhs.Data[j];
                overflow = res[i + j] / TBint::Base;
                res[i + j] %= TBint::Base;
            }
            res[i + rSize] += overflow;
        }
        this->Data = std::move(res);
        return *this;
    }

    TBint operator*(const TBint &lhs, const TBint &rhs) {
        TBint zero;
        if ( lhs == zero || rhs == zero ){
            return zero;
        }
        TBint one (1);
        if (rhs == one){
            return lhs;
        } else if ( lhs == one ){
            return rhs;
        }
        size_t lSize = lhs.Data.size(), rSize = rhs.Data.size();
        TBint res;
        res.Data.resize(lSize + rSize, 0);
        for (int i = 0; i < lSize; ++i){
            int64_t overflow = 0;
            for(int j = 0; j < rSize; ++j){
                res.Data[i + j] += overflow + lhs.Data[i] * rhs.Data[j];
                overflow = res.Data[i + j] / TBint::Base;
                res.Data[i + j] %= TBint::Base;
            }
            res.Data[i + rSize] += overflow;
        }
        return res;
    }


}
