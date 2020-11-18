#ifndef POSTFIX_H_
#define POSTFIX_H_

#include <iostream>
#include <map>

class Postfix{

private:
    int getPrecedence(std::string c, std::map<std::string, int> map);

public:
    std::string InfixToPostfix(std::string infix);
    double PostfixEvaluate(std::string postfix);
};

#endif /* POSTFIX_H_ */