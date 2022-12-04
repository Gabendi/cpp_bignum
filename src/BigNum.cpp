//
// Created by gabor.nemeth on 12/1/22.
//

#include "BigNum.h"

BigNum::BigNum(): _value(""), _sign(1) {

}

BigNum::BigNum(const long long& num): BigNum{std::to_string(num)} {

}

BigNum& BigNum::operator=(const std::string& str) {
    *this = BigNum{str};
    return *this;
}

BigNum::BigNum(const std::string& num) {
    int new_sign = (num[0] == '-') ? -1 : 1;
    _value = new_sign == -1 ? num.substr(1) : num;
    reverse(_value.begin(), _value.end());

    purgeZerosAndSetSign(new_sign);
}

BigNum BigNum::operator+(const BigNum& num) const {
    BigNum curr = *this;
    BigNum other = num;

    if (curr._sign != other._sign)
        return curr - other.neg();

    BigNum res;

    for (int a = 0, carry = 0; a < _value.size() || a < other._value.size() || carry; a++) {
        carry += (a < curr._value.size() ? curr._value[a] - '0' : 0) + (a < other._value.size() ? other._value[a] - '0' : 0);

        res._value += (carry % 10 + '0');

        carry /= 10;
    }

    return res.purgeZerosAndSetSign(_sign);
}

BigNum BigNum::operator-(const BigNum& num) const {
    BigNum curr = *this;
    BigNum other = num;
    
    if (curr._sign != other._sign)
        return curr + other.neg();

    int real_sign = curr._sign;
    curr._sign = 1;

    if (curr < other)
        return ((other - curr).neg()).purgeZerosAndSetSign(-real_sign);

    BigNum res;

    for (int a = 0, carry = 0; a < _value.size(); a++) {
        carry = (curr._value[a] - carry - (a < other._value.size() ? other._value[a] : '0'));

        res._value += (carry >= 0 ? carry + '0' : carry + '0' + 10);

        carry = (carry >= 0 ? 0 : 1);
    }

    return res.purgeZerosAndSetSign(real_sign);
}

BigNum BigNum::operator*(const BigNum& num) const {
    BigNum res("0");
    auto other = num;

    for (int a = 0, b = _value[a] - '0'; a < _value.size(); a++, b = _value[a] - '0') {
        while (b--)
            res = (res + other);

        other.insertZero();
    }

    return res.purgeZerosAndSetSign(_sign * other._sign);
}

BigNum BigNum::operator/(const BigNum& num) const {
    auto other = num;

    if (other.isZero())
        return *this;

    BigNum temp{"0"}, res;

    res._value += std::string(_value.size(), '0');

    int new_sign = _sign * other._sign;
    other._sign = 1;

    for (int i = _value.size() - 1; i >= 0; i--) {
        temp.insertZero();
        temp = temp + BigNum{_value.substr(i, 1)};

        while (!(temp < other)) {
            temp = temp - other;
            res._value[i]++;
        }
    }

    return res.purgeZerosAndSetSign(new_sign);
}

bool BigNum::operator==(const BigNum& num) const {
    return (_sign == num._sign) and (_value == num._value);
}

bool BigNum::operator!=(const BigNum& num) const {
    return !(*this == num);
}

bool BigNum::operator<(const BigNum& other) const {
    if (_sign != other._sign)
        return _sign < other._sign;

    if (_value.size() != other._value.size())
        return (_sign == 1 ? _value.size() < other._value.size() : _value.size() > other._value.size());


    for (int a = _value.size() - 1; a >= 0; a--)
        if (_value[a] != other._value[a])
            return (_sign == 1 ? _value[a] < other._value[a] : _value[a] > other._value[a]);

    return false;
}

bool BigNum::operator>(const BigNum& num) const {
    return !((*this < num) or (*this == num));
}

bool BigNum::operator<=(const BigNum& num) const {
    return (*this < num) or (*this == num);
}

bool BigNum::operator>=(const BigNum& num) const {
    return !(*this < num);
}

BigNum BigNum::operator+() const {
    return *this;
}

BigNum BigNum::operator-() const {
    BigNum num;

    num._value = _value;
    if (!isZero()) {
        num._sign = _sign == 1 ? -1 : 1;
    }

    return num;
}

BigNum& BigNum::operator+=(const BigNum& num) {
    *this = *this + num;

    return *this;
}

BigNum& BigNum::operator-=(const BigNum& num) {
    *this = *this - num;

    return *this;
}

BigNum& BigNum::operator*=(const BigNum& num) {
    *this = *this * num;

    return *this;
}

BigNum& BigNum::operator/=(const BigNum& num) {
    *this = *this / num;

    return *this;
}

std::istream& operator>>(std::istream& in, BigNum& num) {
    std::string input;
    in >> input;
    num = BigNum{input};

    return in;
}

std::ostream& operator<<(std::ostream& out, const BigNum& num) {
    out << num.toString();

    return out;
}

std::string BigNum::toString() const {
    std::string ret = _value;
    std::reverse(ret.begin(), ret.end());

    return (_sign == -1 ? "-" : "") + ret;
}

BigNum& BigNum::neg() {
    _sign *= -1;
    return *this;
}

BigNum& BigNum::purgeZeros() {
    if (isZero())
        return *this;

    auto first_none_zero_from = std::find_if(_value.crbegin(), _value.crend(), [](char c) {return c != '0'; });
    auto num_zeros = std::distance(_value.crbegin(), first_none_zero_from);

    _value.erase(_value.size() - num_zeros, num_zeros);

    return *this;
}

bool BigNum::isZero() const {
    return _value.size() == 1 && _value[0] == '0';
}

void BigNum::setSign(int sign) {
    _sign = isZero() ? 1 : sign;
}

BigNum& BigNum::purgeZerosAndSetSign(int sign) {
    purgeZeros();
    setSign(sign);
    return *this;
}

BigNum& BigNum::insertZero() {
    _value.insert(_value.begin(), '0');
    return *this;
}
