#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <cmath>
#include <string>

#include "postfix.h"


int Postfix::getPrecedence(std::string c, std::map<std::string, int> map){
    auto it = map.find(c);
    return (it == map.end() ? -1 : it->second);
}

        
std::string Postfix::InfixToPostfix(std::string infix){
    std::stack<std::string> operator_stack;
    std::string temp_infix;
    std::vector<std::string> infix_list;
    std::string postfix;

    std::map<std::string, int> operator_precedents = { 
        {"^", 5}, 
        {"*", 4}, {"/", 4}, {"%", 4}, 
        {"+", 3}, {"-", 3}, 
        {"(", 2}, {")", 2}, 
        {"=", 1}};
        
    for(int i=0;i < infix.length();i++){
        std::string t(1, infix[i]);

        if(t == " "){
            infix_list.push_back(temp_infix);
            infix_list.push_back(" ");

            temp_infix = "";
            continue;
        }

        temp_infix.append(t);
    }

    // dump temp_infix into infix_list
    infix_list.push_back(temp_infix);

    for(int i=0;i<infix_list.size();i++){

        if(infix_list[i] == " "){
            postfix += " ";
        }
        
        else if((infix_list[i] == "+") || (infix_list[i] == "-") || (infix_list[i] == "*") || (infix_list[i] == "/") || (infix_list[i] == "^") || (infix_list[i] == "(") || (infix_list[i] == ")") || (infix_list[i] == "%") || (infix_list[i] == "=")){

            if(operator_stack.empty()){
                operator_stack.push(infix_list[i]);
                continue;
            }

            else{
                if(infix_list[i] == "("){
                    operator_stack.push(infix_list[i]);
                    continue;
                }

                else if(infix_list[i] == ")"){
                    while(true){
                        if(operator_stack.empty()){
                            throw ("Stack should not be empty");
                        }

                        if(operator_stack.top() == "("){
                            operator_stack.pop();
                            break;
                        }

                        postfix += operator_stack.top();
                        operator_stack.pop();
                    }
                    continue;
                }      

                else if(infix_list[i] == "="){
                    continue;
                }

                else{ 

                    int current_operator_value = Postfix::getPrecedence(infix_list[i], operator_precedents);
                    int stack_operator_value = Postfix::getPrecedence(operator_stack.top(), operator_precedents);


                    if(current_operator_value > stack_operator_value){

                        operator_stack.push(infix_list[i]);
                    }

                    else if(current_operator_value <= stack_operator_value){
                        for(int i=0;i<operator_stack.size();i++){

                            current_operator_value = Postfix::getPrecedence(infix_list[i], operator_precedents);
                            stack_operator_value = Postfix::getPrecedence(operator_stack.top(), operator_precedents);

                            if(operator_stack.empty()){
                                break;
                            }

                            else if(stack_operator_value >= current_operator_value){
                                postfix += operator_stack.top();
                                operator_stack.pop();
                            }

                            else if(current_operator_value > stack_operator_value){
                                operator_stack.push(infix_list[i]);
                            }
                        }
                    }
                }              
            }
        }
        else{
            postfix += infix_list[i];
        }
    }

    for(int i=0;i<operator_stack.size();i++){
        postfix += " " + operator_stack.top();
        operator_stack.pop();
    }

    return postfix;
}


double Postfix::PostfixEvaluate(std::string postfix){
    std::stack<double> number_stack;
    std::vector<std::string> postfix_list;

    std::string temp_postfix;
    for(int i=0;i<postfix.size();i++){
        std::string t(1, postfix[i]);

        if(t == " "){
            postfix_list.push_back(temp_postfix);
            postfix_list.push_back(" ");

            temp_postfix = "";

            continue;
        }

        temp_postfix.append(t);
    }

    postfix_list.push_back(temp_postfix);

    for(int i=0;i<postfix_list.size();i++){
        double new_value;


        if(postfix_list[i] == "+"){
            double value1 = number_stack.top(); number_stack.pop();
            double value2 = number_stack.top(); number_stack.pop();

            new_value = value1 + value2;
            number_stack.push(new_value);
        }
        else if(postfix_list[i] == "-"){
            double value1 = number_stack.top(); number_stack.pop();
            double value2 = number_stack.top(); number_stack.pop();

            new_value = value2 - value1;
            number_stack.push(new_value);
        }
        else if(postfix_list[i] == "*"){
            double value1 = number_stack.top(); number_stack.pop();
            double value2 = number_stack.top(); number_stack.pop();

            new_value = value2 * value1;
            number_stack.push(new_value);
        }
        else if(postfix_list[i] == "/"){
            double value1 = number_stack.top(); number_stack.pop();
            double value2 = number_stack.top(); number_stack.pop();

            new_value = value2 / value1;
            number_stack.push(new_value);
        }
        else if(postfix_list[i] == "^"){
            double value1 = number_stack.top(); number_stack.pop();
            double value2 = number_stack.top(); number_stack.pop();

            new_value = pow(value2, value1);
            number_stack.push(new_value);
        }
        else if(postfix_list[i] == "%"){
            double value1 = number_stack.top(); number_stack.pop();
            double value2 = number_stack.top(); number_stack.pop();

            new_value = fmod(value2, value1);
            number_stack.push(new_value);
        }
        else if(postfix_list[i] == " "){
            continue;
        }
        else{
            number_stack.push(::atof(postfix_list[i].c_str()));
        }
    }
    double postfix_evaluated = number_stack.top(); number_stack.pop();
    return postfix_evaluated;
}