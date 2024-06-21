#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include "../MyVector/MyVector.h"
#include <cstdint>
#include <string>
#include <stdexcept>
#include <algorithm>

class BigInt {
public:
    BigInt();
    BigInt(std::string);
    BigInt(int64_t);
    BigInt(BigInt&);

    friend BigInt operator+(BigInt, BigInt);
    friend BigInt operator-(BigInt, BigInt);
    friend BigInt operator*(BigInt, BigInt);
    friend BigInt operator/(BigInt, BigInt);
    friend BigInt operator%(BigInt, BigInt);

    bool odd();
    bool operator<(BigInt);
    bool operator>(BigInt);
    bool operator<=(BigInt);
    bool operator>=(BigInt);
    bool operator==(BigInt);

    void rounding(bool invert = false);
    void div_by_two();
    void operator=(BigInt);
    void operator+=(BigInt);
    void operator-=(BigInt);
    void operator*=(BigInt);
    void operator/=(BigInt);
    void operator%=(BigInt);

    friend std::ostream& operator<<(std::ostream &out, BigInt);
    friend std::istream& operator>>(std::istream &in, BigInt&);
private:
    MyVector<int32_t> number;
    int sign;
};

BigInt::BigInt()
    : number(1), sign(0) {}

BigInt::BigInt(std::string num) {
    if(num[0] == '-') {
        sign = -1;
        num.erase(0, 1);
    } else {
        sign = 1;
    }
    number.resize(num.size());
    for(int i{0}; i < num.size(); ++i) {
        if(!isdigit(num[i])) {
            throw std::range_error("Error: found non digit char in the string. (BigInt)\n");
        }
        number[i] = num[num.size() - i - 1] - '0';
    }
}

BigInt::BigInt(int64_t num) {
    if(num < 0) {
        sign = -1;
        num = -num;
    } else {
        sign = 1;
    }
    if(num == 0) {
        number.push_back(0);
    }
    while(num > 0) {
        number.push_back(num % 10);
        num /= 10;
    }
}

BigInt::BigInt(BigInt &num) {
    sign = num.sign;
    number = num.number;
}

BigInt operator+(BigInt a, BigInt b) {
    BigInt ret(a);
    ret += b;
    return ret;
}

BigInt operator-(BigInt a, BigInt b) {
    BigInt ret(a);
    ret -= b;
    return ret;
}

BigInt operator*(BigInt a, BigInt b) {
    BigInt ret;
    ret.number.resize(a.number.size() + b.number.size() + 1);
    for(int i{0}; i < a.number.size(); ++i) {
        for(int j{0}; j < b.number.size(); ++j) {
            ret.number[i + j] += a.number[i] * b.number[j];
        }
        ret.rounding();
    }
    ret.sign = a.sign * b.sign;
    return ret;
}

BigInt operator/(BigInt a, BigInt b) {
    BigInt l(0), r(2);
    int sign = a.sign * b.sign;
    a.sign = b.sign = 1;
    
    while(b * r <= a) {
        r *= BigInt(2);
    }
    BigInt ONE(1);
    while(r - l > ONE) {
        BigInt mid;
        mid = l + r;
        mid.div_by_two();
        if(b * mid <= a) {
            l = mid;
        } else {
            r = mid;
        }
    }
    l.sign = sign;
    l.rounding();
    return l;
}

BigInt operator%(BigInt a, BigInt b) {
    BigInt ret(a);
    ret /= b;
    ret *= b;
    ret = a - ret;
    return ret;
}

void BigInt::operator=(BigInt b) {
    sign = b.sign;
    number = b.number;
}

bool BigInt::odd() {
    return number[0] & 1;
}

bool BigInt::operator<(BigInt b) {
    if(sign != b.sign) return sign < b.sign;
    bool neg{sign == -1};
    if(number.size() != b.number.size())
        return (number.size() < b.number.size()) ^ neg;
    for(int i{int(number.size() - 1)}; i >= 0; --i) {
        if(number[i] != b.number[i]) {
            return (number[i] < b.number[i]) ^ neg;
        }
    }
    return false;
}

bool BigInt::operator>(BigInt b) {
    if(sign != b.sign) return sign > b.sign;
    bool neg{sign == -1};
    if(number.size() != b.number.size())
        return (number.size() > b.number.size()) ^ neg;
    for(int i{int(number.size() - 1)}; i >= 0; --i) {
        if(number[i] != b.number[i]) {
            return (number[i] > b.number[i]) ^ neg;
        }
    }
    return false;
}

bool BigInt::operator<=(BigInt b) {
    return operator<(b) || operator==(b);
}

bool BigInt::operator>=(BigInt b) {
    return operator>(b) || operator==(b);
}

bool BigInt::operator==(BigInt b) {
    if(sign != b.sign) return false;
    if(number.size() != b.number.size()) return false;
    for(int i{int(number.size() - 1)}; i >= 0; --i) {
        if(number[i] != b.number[i]) {
            return false;
        }
    }
    return true;
}

// 10 5 -8 6 -7 30 5  -> 10425605
// -8 -6 -4 -2 0 2 4 6 8 -> -864197532
void BigInt::rounding(bool invert) {
    if(invert) {
        for(int i{0}; i < number.size(); ++i)
            number[i] *= -1;
        sign *= -1;
    }
    for(int i{0}; i < number.size() - 1; ++i) {
        number[i + 1] += number[i] / 10 - (number[i] < 0) + (number[i] < 0 && number[i] % 10 == 0);
        number[i] = (number[i] % 10 + 10) % 10;
    }
    while(number.size() > 1 && number.back() == 0) {
        number.pop_back();
    }
    if(number.back() < 0) {
        sign *= -1;
        number.back() *= -1;
    } else if(number.back() == 0) {
        sign = 1;
    }
}

void BigInt::div_by_two() {
    for(int i{int(number.size() - 1)}; i >= 0; --i) {
        if((i >= 1) && (number[i] & 1)) {
            number[i - 1] += 10;
        }
        number[i] >>= 1;
    }
    rounding();
}

void BigInt::operator+=(BigInt b) {
    bool invert{false};
    if(sign != b.sign) {
        int sg{sign}, bsg{b.sign};
        sign = b.sign = 1;
        if(operator<(b)) {
            invert = true;
        }
        sign = sg;
        b.sign = bsg;
    }
    number.resize(std::max(number.size(), b.number.size()) + 1);
    number.back() = 0;
    for(uint32_t i{0}; i < number.size() - 1; ++i) {
        if(i < b.number.size()) {
            number[i] += b.number[i] * sign * b.sign;
        }
    }
    rounding(invert);
}

void BigInt::operator-=(BigInt b) {
    bool invert{false};
    if(sign == b.sign) {
        int sg{sign}, bsg{b.sign};
        sign = b.sign = 1;
        if(operator<(b)) {
            invert = true;
        }
        sign = sg;
        b.sign = bsg;
    }
    number.resize(std::max(number.size(), b.number.size()) + 1);
    
    number.back() = 0;
    for(uint32_t i{0}; i < number.size() - 1; ++i) {
        if(i < b.number.size()) {
            number[i] -= b.number[i] * sign * b.sign;
        }
    }
    rounding(invert);
}

void BigInt::operator*=(BigInt b) {
    *this = (*this) * b;
}

void BigInt::operator/=(BigInt b) {
    *this = (*this) / b;
}

void BigInt::operator%=(BigInt b) {
    *this = (*this) % b;
}

std::ostream& operator<<(std::ostream &out, BigInt a) {
    if(a.sign == -1) {
        out << '-';
    }
    for(int i{int(a.number.size() - 1)}; i >= 0 ; --i) {
        out << a.number[i];
    }
    return out;
}

std::istream& operator>>(std::istream &in, BigInt &a) {
    std::string sa;
    in >> sa;
    a = BigInt(sa);
    return in;
}

BigInt pow(BigInt, BigInt);
BigInt pow(BigInt a, BigInt x) {
    BigInt ret(1);
    while(x > BigInt(0)) {
        if(x.odd()) ret *= a;
        a *= a;
        x.div_by_two();
    }
    return ret;
}

BigInt gcd(BigInt, BigInt);
BigInt gcd(BigInt a, BigInt b) {
    return (a % b == 0 ? b : gcd(b, a % b));
}

#endif
