#include "big_integer.hpp"

namespace NBigInt {
    TBint::TBint(int64_t a) {
        if (a < TBint::BASE) {
            if (a != 0) {
                this->Data.push_back(a);
            }
            return;
        }
        do {
            this->Data.push_back(a % TBint::BASE);
            a /= TBint::BASE;
        } while (a > 0);
        this->DeleteLeadingZeroes();
    }

    TBint::TBint(const std::string &str) {
        int newSize = ceil(static_cast<double> (str.size()) / TBint::RADIX);
        this->Data.resize(newSize);
        for ( int rBorder = str.size(), digit = 0; rBorder > 0; rBorder -= TBint::RADIX, ++digit) {
            int nextBorder = rBorder - TBint::RADIX;
            int lBorder = (nextBorder <= 0) ? 0 : nextBorder;
            TSpan<std::basic_string, char> curSeg (str, lBorder, rBorder); // Создаем отрезок для перевода
            this->Data[digit] = StrToll(curSeg);
        }
        this->DeleteLeadingZeroes();
    }

    void TBint::DeleteLeadingZeroes() noexcept {
        while (!this->Data.empty() && this->Data.back() == 0) {

            this->Data.pop_back();
        }
    }

    TBint &TBint::operator+=(const TBint &rhs) {
        int lSize = this->Data.size(), rSize = rhs.Data.size();
        int m = std::max(lSize, rSize);
        this->Data.resize(m, 0);
        int64_t overflow = 0;
        for (int i = 0; i < m; ++i) {
            this->Data[i] += overflow;
            if (i < rSize) {
                this->Data[i] += rhs.Data[i];
            }
            //TODO смотреть на что не переполняется в отрицательное
            overflow = this->Data[i] / TBint::BASE;
            this->Data[i] = this->Data[i] % TBint::BASE;
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

        for ( auto it = rhs.Data.rbegin() + 1; it < rhs.Data.rend(); ++it ){
            os << std::setfill('0') << std::setw(TBint::RADIX) << *it;
        }
        os << std::resetiosflags(std::ios_base::basefield);
        return os;
    }

    TBint &TBint::operator-=(const TBint &rhs) {
#ifdef EXCEPTION_OPT
        if ( *this < rhs ){
            throw std::underflow_error("lhs less then rhs");
        }
#endif
        int lSize = this->Data.size(), rSize = rhs.Data.size();
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
                this->Data[i] += TBint::BASE;
            }
            this->Data[i] = this->Data[i] % TBint::BASE;
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
        for (int i = lhs.Data.size() - 1; i >= 0; --i) {
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
        for (int i = lhs.Data.size() - 1; i >= 0; --i) {
            if (lhs.Data[i] != rhs.Data[i]) {
                return lhs.Data[i] > rhs.Data[i];
            }
        }
        return false;
    }

    bool operator==(const TBint &lhs, const TBint &rhs) {
        int lSize = lhs.Data.size(), rSize = rhs.Data.size();
        if (lSize != rSize) {
            return false;
        }
        for (int i = 0; i < lSize; i++) {
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
            int leadingZeroes = TBint::RADIX - tmp.size();
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
        *this = TBint::ChooseVersionOfMul( *this, rhs );
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
        TBint res = TBint::ChooseVersionOfMul(lhs, rhs);
        return res;

    }

    std::vector<int64_t> TBint::NaiveMul(const TSpan <std::vector, int64_t> &rhs, const TSpan <std::vector, int64_t> &lhs) {
        auto lSize = rhs.Size(), rSize = lhs.Size();
        std::vector<int64_t> res;
        res.resize(lSize + rSize, 0);
        for (auto i = 0; i < lSize; ++i){
            for(auto j = 0; j < rSize; ++j){
                res[i + j] += rhs[i] * lhs[j];
            }
        }
        return res;
    }

    void TBint::Finalize(std::vector<int64_t> &res){
        int64_t overflow = 0;
        for (int64_t& re : res){
            re += overflow;
            overflow = re / TBint::BASE;
            re %= TBint::BASE;
        }
        if (overflow){
            res.push_back(overflow);
        }
    }

    std::vector<int64_t> TBint::KaratsubaMul(const TSpan <std::vector, int64_t> &x, const TSpan <std::vector, int64_t> &y) {
        int n = x.Size();
        if (n <= TBint::KARATSUBA_NUMBER){
            auto res = TBint::NaiveMul(x,y);
            res.resize(2*n,0);
            return res;
        }
        int k = n >> 1; // analog n / 2;
        std::vector<int64_t> res (n * 2);


        TSpan<std::vector, int64_t> xr (x.v, x.begin, x.begin + k);
        TSpan<std::vector, int64_t> xl (x.v, x.begin + k, x.end);
        TSpan<std::vector, int64_t> yr (y.v, y.begin, y.begin + k);
        TSpan<std::vector, int64_t> yl (y.v, y.begin + k, y.end);

        std::vector<int64_t> p1 = TBint::KaratsubaMul(xl, yl);
        std::vector<int64_t> p2 = TBint::KaratsubaMul(xr, yr);

        std::vector<int64_t> xlr(k);
        std::vector<int64_t> ylr(k);

        for (auto i = 0; i < k; ++i) {
            xlr[i] = xl[i] + xr[i];
            ylr[i] = yl[i] + yr[i];
        }

        std::vector<int64_t> p3 = TBint::KaratsubaMul(xlr, ylr);
        for (auto i = 0; i < n; ++i) {
            p3[i] -= p2[i] + p1[i];
        }
        for (auto i = 0; i < n; ++i) {
            res[i] = p2[i];
        }
        for (auto i = n; i < 2 * n; ++i) {
            res[i] = p1[i - n];
        }
        for (auto i = k; i < n + k; ++i) {
            res[i] += p3[i - k];
        }
        return res;

    }

    TBint TBint::ChooseVersionOfMul(const TBint &lhs, const TBint &rhs) {
        TBint res;
        size_t n = std::max(lhs.Data.size(), rhs.Data.size());
        n = ClosestPower2(n);
        if ( n > TBint::KARATSUBA_NUMBER ){
            auto& l = const_cast<TBint&>(lhs); // It is bad, but ClosestPower2 guarantees that n >= old size
            auto& r = const_cast<TBint&>(rhs);
            l.Data.resize(n, 0);
            r.Data.resize(n, 0);
            res.Data = TBint::KaratsubaMul( lhs.Data, rhs.Data ); // KaratsubaMul guarantees that lhs, rhs are const
            l.DeleteLeadingZeroes();
            r.DeleteLeadingZeroes();
        }else{
            res.Data = TBint::NaiveMul( lhs.Data, rhs.Data );
        }
        TBint::Finalize(res.Data);
        res.DeleteLeadingZeroes();
        return res;
    }

    TBint &TBint::operator/=(const TBint &rhs) {
        TBint zero;
#ifdef EXCEPTION_OPT
        if ( rhs == zero ){
            throw std::underflow_error("Deviation by zero");
        }
#endif
        if (*this == zero){
            return  *this;
        }
        TBint one (1);
        if (rhs == one){
            return *this;
        }else if (*this < rhs ){
            *this = std::move(zero);
            return *this;
        }else if ( *this == rhs ){
            *this = std::move(one);
            return *this;
        }
        *this = TBint::LongDivWay( *this, rhs );
        return *this;
    }

    TBint operator/(const TBint &lhs, const TBint &rhs) {
        TBint zero;
#ifdef EXCEPTION_OPT
        if ( rhs == zero ){
            throw std::underflow_error("Deviation by zero");
        }
#endif
        if (lhs == zero){
            return  lhs;
        }
        TBint one (1);
        if (rhs == one){
            return lhs;
        }else if (lhs < rhs ){
            return zero;
        }else if ( lhs == rhs ){
            return one;
        }
        TBint res = TBint::LongDivWay( lhs, rhs );
        return res;
    }

    TBint TBint::LongDivWay(const TBint &lhs, const TBint &rhs) {
        std::vector<TBint> preCalculate;
        preCalculate.reserve(TBint::BASE);
        preCalculate.emplace_back(0);
        preCalculate.push_back(rhs);
        TBint tmp = rhs;
        for ( int i = 2; i < TBint::BASE; ++i ){
            tmp += rhs;
            preCalculate.push_back(tmp);
        }
        int lSize = lhs.Data.size(), rSize = rhs.Data.size();
        TBint ost;

        ost.Data.resize(rSize);
        for (auto i = 1; i <= rSize; ++i ){
            ost.Data[rSize - i] = lhs.Data[lSize - i];
        }

        std::vector<int64_t> preRes;
        preRes.reserve( lSize >> 1 ); // reserve lSize/2 memory
        //TODO проверить граници и разряды
        for (int i = rSize; i <= lSize; ++i ){
            int fraction = TBint::BinSearchHelper(ost, preCalculate);
            ost -= preCalculate[fraction];
            preRes.push_back(fraction);
            ost.Data.insert(ost.Data.begin(),lhs.Data[lSize - i - 1]);
        }
        TBint res;
        res.Data.reserve(preRes.size());
        int leadingZero = 0;
        while (preRes[leadingZero] == 0){
            ++leadingZero;
        }

        for (int i  = preRes.size() - 1; i >= leadingZero; --i){
            res.Data.push_back(preRes[i]);
        }
        res.DeleteLeadingZeroes();
        return res;
    }

    int64_t TBint::BinSearchHelper(const TBint& ost, const std::vector<TBint> &preCalculated) {
        int l = 0, r = TBint::BASE;
        while (r - 1 > l){
            int m = (r + l) >> 1; // analog (r + l) / 2
            if (ost < preCalculated[m]){
                r = m;
            }else{
                l = m;
            }
        }
        int64_t res = (r + l) >> 1;
        return res;
    }

    TBint pow(TBint a, const TBint& bigN) {
        TBint zero;
        TBint one (1);
        if (bigN == zero || a == one){
            return one;
        } else if (a == zero){
            return zero;
        }else if (bigN == one){
            return a;
        }
        TBint& res = one; // res = 1;
        for (long n : bigN.Data){
            while(n){
                if (n & 1){
                    res *= a;
                }
                a *= a;
                n >>= 1;
            }
        }
        return res;
    }
}

