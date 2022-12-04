//
// Created by gabor.nemeth on 12/1/22.
//

#include "ExpressionReader.h"
#include "expression.h"

/// Code extended from one of the labs
std::shared_ptr<Expression> ExpressionReader::from_istream(std::istream &stream) {
    std::string word;
    std::stack<std::shared_ptr<Expression>> stack;

    while (std::getline(stream, word)) {
        if (word.empty())
            break;

        if (word == "+"){
            auto first = stack.top();
            stack.pop();
            auto second = stack.top();
            stack.pop();

            std::shared_ptr<Expression> addition{new Sum{first, second}};
            stack.push(addition);
        }
        else if (word == "-"){
            auto first = stack.top();
            stack.pop();
            auto second = stack.top();
            stack.pop();

            std::shared_ptr<Expression> addition{new Subtract{first, second}};
            stack.push(addition);
        }
        else if (word == "*") {
            auto first = stack.top();
            stack.pop();
            auto second = stack.top();
            std::shared_ptr<Expression> product{new Product{first, second}};
            stack.pop();
            stack.push(product);
        }
        else if (word == "/") {
            auto first = stack.top();
            stack.pop();
            auto second = stack.top();
            std::shared_ptr<Expression> product{new Division{first, second}};
            stack.pop();
            stack.push(product);
        }
        else {
            std::shared_ptr<Expression> constant{new Constant{word}};
            stack.push(constant);
        }
    }

    return stack.top();
}
