//
// Created by gabor.nemeth on 12/1/22.
//

#ifndef HF_02_BIGNUM_H
#define HF_02_BIGNUM_H


#include <string>
#include <algorithm>
#include <iostream>

class BigNum {
    std::string _value;
    int _sign;

public:
    BigNum();
    explicit BigNum(const long long&);
    explicit BigNum(const std::string&);
    BigNum(const BigNum&) = default;
    BigNum(BigNum&&) = default;

    BigNum& operator=(const BigNum&) = default;
    BigNum& operator=(BigNum&&) = default;
    BigNum& operator=(const std::string&);

    BigNum operator+(const BigNum&) const;
    BigNum operator-(const BigNum&) const;
    BigNum operator*(const BigNum&) const;
    BigNum operator/(const BigNum&) const;

    bool operator<(const BigNum&) const;
    bool operator>(const BigNum&) const;
    bool operator<=(const BigNum&) const;
    bool operator>=(const BigNum&) const;
    bool operator==(const BigNum&) const;
    bool operator!=(const BigNum&) const;

    BigNum operator+() const;
    BigNum operator-() const;

    BigNum& operator+=(const BigNum&);
    BigNum& operator-=(const BigNum&);
    BigNum& operator*=(const BigNum&);
    BigNum& operator/=(const BigNum&);

    friend std::istream& operator>>(std::istream&, BigNum&);
    friend std::ostream& operator<<(std::ostream&, const BigNum&);
    std::string toString() const;

    void setSign(int);

    BigNum& neg();
    BigNum& insertZero();
    BigNum& purgeZeros();
    BigNum& purgeZerosAndSetSign(int);
    bool isZero() const;

    virtual ~BigNum() = default;
};



#endif //HF_02_BIGNUM_H
