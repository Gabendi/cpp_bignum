//
// Created by gabor.nemeth on 12/1/22.
//

#include "BigNum.h"

BigNum::BigNum(): value(""), sign(1) {

}

BigNum::BigNum(const long long& num): BigNum{std::to_string(num)} {

}

BigNum &BigNum::operator=(const std::string& str) {
    *this = BigNum{str};
    return *this;
}

BigNum::BigNum(const std::string& num) {
    int newSign = (num[0] == '-' ? -1 : 1);
    value = newSign == -1 ? num.substr(1) : num;
    reverse(value.begin(), value.end());

    this->normalize(newSign);
}


BigNum BigNum::operator+(const BigNum& num) const {
    BigNum curr = *this;
    BigNum other = num;

    if (curr.sign != other.sign)
        return curr - other.negative();

    BigNum res;

    for (int a = 0, carry = 0; a < value.size() || a < other.value.size() || carry; a++) {
        carry += (a < curr.value.size() ? curr.value[a] - '0' : 0) + (a < other.value.size() ? other.value[a] - '0' : 0);

        res.value += (carry % 10 + '0');

        carry /= 10;
    }

    return res.normalize(sign);
}

BigNum BigNum::operator-(const BigNum& num) const {
    BigNum curr = *this;
    BigNum other = num;
    
    if (curr.sign != other.sign)
        return curr + other.negative();

    int realSign = curr.sign;

    curr.sign = 1;

    if (curr < other)
        return ((other - curr).negative()).normalize(-realSign);

    BigNum res;

    for (int a = 0, borrow = 0; a < value.size(); a++) {
        borrow = (curr.value[a] - borrow - (a < other.value.size() ? other.value[a] : '0'));

        res.value += (borrow >= 0 ? borrow + '0' : borrow + '0' + 10);

        borrow = (borrow >= 0 ? 0 : 1);
    }

    return res.normalize(realSign);
}


bool BigNum::operator==(const BigNum& num) const {
    return (sign == num.sign) and (value == num.value);
}


bool BigNum::operator!=(const BigNum& num) const {
    return !(*this == num);
}

bool BigNum::operator<(const BigNum& other) const {
    if (sign != other.sign)
        return sign < other.sign;

    if (value.size() != other.value.size())
        return (sign == 1 ? value.size() < other.value.size() : value.size() > other.value.size());

    for (auto a = value.size() - 1; a >= 0; a--)
        if (value[a] != other.value[a])
            return (sign == 1 ? value[a] < other.value[a] : value[a] > other.value[a]);

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

BigNum BigNum::operator*(const BigNum& num) const {
    BigNum res("0");
    auto other = num;
    
    for (int a = 0, b = value[a] - '0'; a < value.size(); a++, b = value[a] - '0') {
        while (b--)
            res = (res + other);

        other.value.insert(other.value.begin(), '0');
    }

    return res.normalize(sign * other.sign);
}


BigNum BigNum::operator+() const {
    return *this;
}

BigNum BigNum::operator-() const {
    BigNum temp;

    temp.value = value;
    if (value != "0") {
        if (sign == 1)
            temp.sign = -1;
        else
            temp.sign = 1;
    }

    return temp;
}

BigNum BigNum::operator/(const BigNum& num) const {
    auto other = num;

    if (other.value.size() == 1 && other.value[0] == '0')
        other.value[0] /= (other.value[0] - '0');

    BigNum temp("0"), res;

    for (int a = 0; a < value.size(); a++)
        res.value += "0";

    int newSign = sign * other.sign;

    other.sign = 1;

    for (int a = value.size() - 1; a >= 0; a--) {
        temp.value.insert(temp.value.begin(), '0');
        temp = temp + BigNum{value.substr(a, 1)};

        while (!(temp < other)) {
            temp = temp - other;
            res.value[a]++;
        }
    }

    return res.normalize(newSign);
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
    std::string ret = value;
    std::reverse(ret.begin(), ret.end());

    return (sign == -1 ? "-" : "") + ret;
}

BigNum &BigNum::negative() {
    sign *= -1;
    return *this;
}

BigNum &BigNum::normalize(int newSign) {
    for (auto a = value.size() - 1; a > 0 && value[a] == '0'; a--)
        value.erase(value.begin() + a);

    sign = (value.size() == 1 && value[0] == '0' ? 1 : newSign);
    return *this;

}
