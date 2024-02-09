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
    BigInt(const BigInt&);

    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator%(const BigInt&, const BigInt&);

    void operator+=(BigInt&);
    void operator-=(BigInt&);
    void operator*=(BigInt&);
    void operator/=(BigInt&);
    void operator%=(BigInt&);

    friend std::ostream& operator<<(std::ostream &out, BigInt&);
    friend std::istream& operator>>(std::istream &in, BigInt&);
private:
    MyVector<int16_t> number;
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
    for(int i{num.size() - 1}; i >= 0; --i) {
        if(!isdigit(num[i])) {
            throw std::range_error("Error: found non digit char in the string. (BigInt)\n");
        }
        number[i] = num[i] - '0';
    }
}

BigInt::BigInt(int64_t num) {
    if(num < 0) {
        sign = -1;
        num = -num;
    } else {
        sign = 1;
    }
    while(num > 0) {
        number.push_back(num % 10);
        num /= 10;
    }
}

BigInt::BigInt(const BigInt &num) {
    sign = num.sign;
    number = num.number;
}

BigInt operator+(const BigInt &a, const  BigInt &b) {
    BigInt ret(a);
    ret += b;
    return ret;
}

BigInt operator-(const BigInt &a, const  BigInt &b) {
    BigInt ret(a);
    ret -= b;
    return ret;
}

BigInt operator*(const BigInt &a, const  BigInt &b) {
    BigInt ret(a);
    ret /= b;
    return ret;
}

BigInt operator%(const BigInt &a, const  BigInt &b) {
    BigInt ret(a);
    ret %= b;
    return ret;
}

void BigInt::operator+=(BigInt &b) {
    number.resize(std::max(number.size(), b.number.size()) + 1);
    for(int i{0}; i < number.size() - 1; ++i) {
        if(b.number.size() <= i) {
            continue;
        }
        number[i] += b.number[i];
        number[i + 1] += number[i] / 10;
        number[i] %= 10;
    }
}

#endif