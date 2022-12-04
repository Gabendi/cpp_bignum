//
// Created by gabor.nemeth on 12/1/22.
//

#ifndef HF_02_EXPRESSION_H
#define HF_02_EXPRESSION_H

#include <iostream>
#include <memory>
#include <utility>
#include "BigNum.h"


/// Expression source code used from lab 4 with minor modifications involved

class Expression {
public:
    virtual BigNum evaluate() const = 0;

    Expression() = default;
    Expression(Expression const &) = default;

private:
    virtual void print(std::ostream &os) const = 0;
    friend std::ostream & operator<<(std::ostream & os, Expression const &e);
};


inline std::ostream & operator<<(std::ostream & os, Expression const &e) {
    e.print(os);
    return os;
}


class Constant final : public Expression {
public:
    explicit Constant(const std::string& c): _c{c} {}
    explicit Constant(BigNum c): _c{std::move(c)} {}

    virtual BigNum evaluate() const override {
        return _c;
    }

    BigNum get_value() const {
        return _c;
    }

private:
    BigNum _c;

    virtual void print(std::ostream &os) const override {
        os << _c;
    }
};


class TwoOperand : public Expression {
public:
    /* create object, adopt dynamically allocated expressions */
    TwoOperand(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) : _lhs{std::move(lhs)}, _rhs{std::move(rhs)} {}

    /* copy constructor */
    TwoOperand(TwoOperand const & the_other)
            : Expression{*this}
            , _lhs{the_other._lhs}, _rhs{the_other._rhs} {
    }

    /* no copy assignment */
    TwoOperand & operator=(TwoOperand const &) = delete;

    virtual BigNum evaluate() const override final {
        return do_operator(_lhs->evaluate(), _rhs->evaluate());
    }

private:
    virtual void print(std::ostream &os) const override final {
        os << '(' << *_lhs << get_operator() << *_rhs << ')';
    }

    /* subclass has to provide function to return its operator */
    virtual char get_operator() const = 0;

    /* subclass has to provide function to do the calculation */
    virtual BigNum do_operator(BigNum lhs, BigNum rhs) const = 0;

protected:
    /* left and right hand side operands */
    std::shared_ptr<Expression> _lhs, _rhs;

};


class Sum final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override {
        return '+';
    }

    BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs + rhs;
    }

};

class Subtract final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    char get_operator() const override {
        return '-';
    }

    BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs - rhs;
    }
};

class Product final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    char get_operator() const override {
        return '*';
    }

    BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs * rhs;
    }
};

class Division final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    char get_operator() const override {
        return '/';
    }

    BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs / rhs;
    }
};

#endif //HF_02_EXPRESSION_H
