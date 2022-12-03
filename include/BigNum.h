//
// Created by gabor.nemeth on 12/1/22.
//

#ifndef HF_02_BIGNUM_H
#define HF_02_BIGNUM_H


#include <string>
#include <algorithm>
#include <iostream>

class BigNum {
    std::string value;
    int sign;

public:
    BigNum();
    explicit BigNum(const long long&);
    explicit BigNum(const std::string&);
    BigNum(const BigNum&) = default;
    BigNum(BigNum&& num) = default;

    BigNum& operator=(const BigNum& num) = default;
    BigNum& operator=(BigNum&& num) = default;
    BigNum& operator=(const std::string& x);

    BigNum operator+() const;
    BigNum operator-() const;

    BigNum& negative();
    BigNum& normalize(int newSign);

    BigNum operator+(const BigNum&) const;
    BigNum operator-(const BigNum&) const;
    BigNum operator*(const BigNum&) const;
    BigNum operator/(const BigNum&) const;

    BigNum& operator+=(const BigNum&);
    BigNum& operator-=(const BigNum&);
    BigNum& operator*=(const BigNum&);
    BigNum& operator/=(const BigNum&);

    bool operator<(const BigNum&) const;
    bool operator>(const BigNum&) const;
    bool operator<=(const BigNum&) const;
    bool operator>=(const BigNum&) const;
    bool operator==(const BigNum&) const;
    bool operator!=(const BigNum&) const;

    friend std::istream& operator>>(std::istream&, BigNum&);
    friend std::ostream& operator<<(std::ostream&, const BigNum&);
    std::string toString() const;

    virtual ~BigNum() = default;
};



#endif //HF_02_BIGNUM_H
