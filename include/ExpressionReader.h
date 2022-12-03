//
// Created by gabor.nemeth on 12/1/22.
//

#ifndef HF_02_EXPRESSIONREADER_H
#define HF_02_EXPRESSIONREADER_H


#include <iostream>
#include <fstream>
#include <stack>
#include <memory>
#include "expression.h"

class ExpressionReader {
public:
    static std::shared_ptr<Expression> from_istream(std::istream &stream);
};


#endif //HF_02_EXPRESSIONREADER_H
