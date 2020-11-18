#include <iostream>
#include <string>

#include "postfix.h"

int main()
{

    Postfix postfixMachine;

    std::cout << "[+] Type help for help" << std::endl;

    while(true){
        std::string input1;
        std::cout << "[+] What do ya want to do?:";
        std::getline(std::cin, input1);

        if((input1 == "help") || (input1 == "h")){
            std::cout << "[+] Options:" << std::endl;

            std::cout << "  -infix2postfix: converts infix expressions to postfix expressions (GAPS ARE NEEDED BETWEEN OPERANDS AND OPERATORS" << std::endl;
            std::cout << "  -postfixeval: Evaluates postfix expressions" << std::endl;
            std::cout << "  -exit: exits the program" << std::endl;

            std::cout << "\n";
        }

        else if(input1 == "infix2postfix"){
            std::cout << "[+] Infix expression to convert: ";
            std::getline(std::cin, input1);

            std::cout << "\n";

            std::string convertedInfix = postfixMachine.InfixToPostfix(input1);
            std::cout << "Postfix: " << convertedInfix << std::endl;
        }

        else if(input1 == "postfixeval"){
            std::cout << "[+] Postfix expression to evaluate: ";
            std::getline(std::cin, input1);

            std::cout << "\n";

            double evaluatedPostfix = postfixMachine.PostfixEvaluate(input1);
            std::cout << "Evaluated: " << evaluatedPostfix << std::endl;
        }

        else if((input1 == "exit") || (input1 == "e")){
            std::cout << "[+] Exiting..." << std::endl;
            exit(0);
        }

        else{
            std::cout << "[-] Invalid option, please try again" << std::endl;
            std::cout << "\n" << std::endl;
        }
    }
    return 0;
}
