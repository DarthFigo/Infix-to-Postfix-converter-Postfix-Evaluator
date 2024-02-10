"""InfixToPostfixConverter.py: Converts infix expressions to postfix expressions"""
from time import sleep
import re


class StackEmpty(Exception):
    pass


class InfixToPostfixConverter:
    # take the infix expression as a parameter, create operator precedence
    def __init__(self, infix):
        self.postfix = ''
        self.infix = infix
        self.operators = {'^': 5,
                         '*': 4, '/': 4,
                         '+': 3, '-': 3,
                         '(': 2, ')': 2,
                         '=': 1}

        self.convert()

    def convert(self):
        # create stack and split every character in infix string into a list while removing all the whitespace
        stack = []
        list_infix = list(self.infix.replace(" ", ""))

        # loop over every character in the infix list
        for char in list_infix:

            # if the character is a letter or a number, then add to postfix string
            if (char.isalpha()) or (char.isdigit()):
                self.postfix = self.postfix + " " + char
                continue

            else:
                # if stack is empty, push the operator into the stack
                if not stack:
                    stack.append(char)
                    continue

                # if there already is an operator in the stack
                else:
                    # check if its the start of a bracket, if it is then push it to the stack
                    if char == "(":
                        stack.append(char)
                        continue

                    # check if its the end of a bracket, if it is then loop through the stack and pop all values
                    # + add them to the postfix string until it reaches the open bracket
                    elif char == ")":
                        while True:
                            if not stack:
                                raise StackEmpty("Stack should not be empty at this point")

                            value = stack[-1]
                            if value == "(":
                                stack.pop()
                                bracket_stuff_done = True
                                break

                            self.postfix = self.postfix + " " + stack.pop()

                        if bracket_stuff_done:
                            continue

                    # if there is an = operator, then ignore it
                    elif char == "=":
                        continue

                    # get the precedents of the operators
                    char_operator_value = self.operators[char]
                    try:
                        stack_operator_value = self.operators[stack[-1]]
                    except IndexError:
                        pass

                    # if precedence of the char is bigger than the precedence of the operator in the stack then add the char to the stack
                    if char_operator_value > stack_operator_value:
                        stack.append(char)
                        continue

                    # if the precedence of the operand in the stack is bigger than the precedence of char...
                    elif stack_operator_value >= char_operator_value:
                        # loop over the stack
                        for i in range(len(stack)):

                            # get precedence of the operators
                            char_operator_value = self.operators[char]
                            try:
                                stack_operator_value = self.operators[stack[-1]]
                            except IndexError:
                                pass

                            # if the stack is empty then break
                            if not stack:
                                break

                            # if the precedence of the operand in the stack is bigger than the precedence of char then
                            # pop the stack and add it to the postfix string
                            elif stack_operator_value >= char_operator_value:
                                self.postfix = self.postfix + " " + stack.pop()

                            # if precedence of the char is bigger than the precedence of the operand in the stack then add the char to the stack
                            elif char_operator_value > stack_operator_value:
                                stack.append(char)

                        # at the end add the char to the stack after looping over the stack
                        stack.append(char)

        # dump stack
        for i in range(len(stack)):
            self.postfix = self.postfix + " " + stack.pop()

        return self.infix, self.postfix


if __name__ == "__main__":
    print("[+] WARNING: DOES NOT WORK WITH FLOATS")
    print("[+] Press ENTER to exit\n")
    sleep(1)

    while True:
        # ask user for the infix expression to convert
        infix = str(input("[+] Infix Expression: "))

        # if the user inputted enter, then close the program
        if infix == '':
            exit(0)

        # convert the infix expression to postfix, and print the output
        converter = InfixToPostfixConverter(infix)
        print("[+] Infix: %s ---> Postfix: %s \n" % (converter.infix, converter.postfix))
