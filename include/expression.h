//
// Created by gabor.nemeth on 12/1/22.
//

#ifndef HF_02_EXPRESSION_H
#define HF_02_EXPRESSION_H

#include <iostream>
#include <memory>
#include "BigNum.h"


/// Expression source code used from lab 4 with minor modifications involved

class Expression {
public:
    virtual BigNum evaluate(BigNum x) const = 0;

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
    Constant(std::string c): c_{c} {}
    Constant(BigNum c): c_{c} {}

    virtual BigNum evaluate(BigNum) const override {
        return c_;
    }

    BigNum get_value() const {
        return c_;
    }

private:
    BigNum c_;

    virtual void print(std::ostream &os) const override {
        os << c_;
    }
};


class Variable final : public Expression {
public:
    virtual BigNum evaluate(BigNum x) const override {
        return x;
    }

private:
    virtual void print(std::ostream &os) const override {
        os << 'x';
    }
};


class TwoOperand : public Expression {
public:
    /* create object, adopt dynamically allocated expressions */
    TwoOperand(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) : lhs_{lhs}, rhs_{rhs} {}

    /* copy constructor */
    TwoOperand(TwoOperand const & the_other)
            : Expression{*this}
            , lhs_{the_other.lhs_}, rhs_{the_other.rhs_} {
    }

    /* no copy assignment */
    TwoOperand & operator=(TwoOperand const &) = delete;

    virtual BigNum evaluate(BigNum x) const override final {
        return do_operator(lhs_->evaluate(x), rhs_->evaluate(x));
    }

private:
    virtual void print(std::ostream &os) const override final {
        os << '(' << *lhs_ << get_operator() << *rhs_ << ')';
    }

    /* subclass has to provide function to return its operator */
    virtual char get_operator() const = 0;

    /* subclass has to provide function to do the calculation */
    virtual BigNum do_operator(BigNum lhs, BigNum rhs) const = 0;

protected:
    /* left and right hand side operands */
    std::shared_ptr<Expression> lhs_, rhs_;

};


class Sum final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override {
        return '+';
    }

    virtual BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs + rhs;
    }

};

class Subtract final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override {
        return '-';
    }

    virtual BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs - rhs;
    }
};

class Product final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override {
        return '*';
    }

    virtual BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs * rhs;
    }
};

class Division final : public TwoOperand {
public:
    using TwoOperand::TwoOperand;

private:
    virtual char get_operator() const override {
        return '/';
    }

    virtual BigNum do_operator(BigNum lhs, BigNum rhs) const override {
        return lhs / rhs;
    }
};

#endif //HF_02_EXPRESSION_H
