"""PostfixEvaluator.py: Evaluates postfix expressions"""
from time import sleep


class UnknownOperator(Exception):
    pass


class PostfixEvaluator:
    # take the postfix expression as a parameter
    def __init__(self, postfix):
        self.postfix = postfix
        self.postfix_evaluate = 0

        self.evaluate()

    # create stack and split the postfix expression into a list
    def evaluate(self):
        stack = []
        postfix_list = self.postfix.split()

        # iterate over every character in the list
        for char in postfix_list:
            new_value = 0

            # check if the character is any of the supported characters
            if char == "+":
                # pop the top 2 values from the stack
                value1 = float(stack.pop())
                value2 = float(stack.pop())

                # complete the operation on the two values and add the result to the stack
                new_value = value2 + value1
                stack.append(new_value)

            elif char == "-":
                value1 = float(stack.pop())
                value2 = float(stack.pop())
                new_value = value2 - value1
                stack.append(new_value)

            elif char == "*":
                value1 = float(stack.pop())
                value2 = float(stack.pop())
                new_value = value2 * value1
                stack.append(new_value)

            elif char == "/":
                value1 = float(stack.pop())
                value2 = float(stack.pop())
                new_value = value2 / value1
                stack.append(new_value)

            elif char == "^":
                value1 = float(stack.pop())
                value2 = float(stack.pop())
                new_value = value2 ** value1
                stack.append(new_value)

            elif char == "%":
                value1 = float(stack.pop())
                value2 = float(stack.pop())
                new_value = value2 % value1
                stack.append(new_value)

            # if the character isn't an operator, check if it is an operand
            elif type(float(char)) == float:
                stack.append(char)

            # if the character isn't a supported operator and isn't an operand, then raise an UnknownOperator error
            else:
                raise UnknownOperator("Unknown operator: %s" % char)

        # put the evaluated postfix expression into a variable and return it to be able to print it in main()
        self.postfix_evaluate = stack[0]
        return self.postfix_evaluate


if __name__ == "__main__":
    print("[+] WARNING: THE POSTFIX EXPRESSION MUST HAVE SPACES BETWEEN EACH OPERATOR/OPERAND")
    print("[+] Press ENTER to exit \n")
    sleep(1)

    while True:
        # ask the user to input the postfix expression
        postfix = str(input("[+] Postfix Expression: "))

        # if the value inputted is nothing (if they pressed enter) then exit
        if postfix == '':
            exit(0)

        # convert the postfix expression and print the output
        evaluator = PostfixEvaluator(postfix)
        print("Postfix: %s -----------------> Evaluated: %s \n" % (evaluator.postfix, evaluator.postfix_evaluate))
