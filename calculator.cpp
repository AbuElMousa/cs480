// File Name: calculator.cpp
// Author: Muad Shahin
// Student ID: e626z726
// Assignment Number: 5
// Last Changed: Apr 13, 2015
// Description: a calculator using the following two-stage process. The first stage reads in an expression entered by
// the user in regular infix notation (such as “(2 + 3) * 4”) and converts the expression to postfix notation
// (such as “2 3 + 4 *”). The second stage then evaluates the postfix expression and displays the result. For the
// first stage, a stack of characters will be used, and for the second stage a stack of numbers. Only one stack type
// will be created, but it will be a template class so that it can be instantiated to provide both stack types which
// are needed.

#include <iostream>
#include <string>
#include <stdlib.h>
#include "calculator.hpp"
#include "stack.hpp"

using namespace std;

int main()
{
    string infix;
    string postfix;
    cout << endl << "Enter an expression in infix notation:   ";
    cin >> infix;
    infix2postfix(infix, postfix);
    cout << "Your expression converted to postfix is: " << postfix << endl;
    double result = evaluate_postfix(postfix);
    cout << endl << "The result of evaluating your expression is: " << result << endl << endl;
    cout << endl << "Heap Cleaned!" << endl << endl;

    return 0;
}

bool isOperator(char ch)
{
    if (ch == '-' || ch == '+' || ch == '(' || ch == '/' || ch == '*')
        return true;

    return false;
}

bool isOperand(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;

    return false;
}

bool infix2postfix(string infx, string& postfx)
{
    Stack<char> charStack;
    for (string::iterator it=infx.begin(); it!=infx.end(); it++)
    {
        if (*it == ')')
        {
            while(charStack.top() != '(')
            {
                postfx += charStack.pop();
            }

            charStack.pop();
        }

        if (isOperator(*it))
            charStack.push(*it);

        if (isOperand(*it))
            postfx += *it;
    }
    if (!charStack.is_empty())
        postfx += charStack.pop();

    return true;
}

double evaluate_postfix(string postfx)
{
    Stack<double> doubleStack;
    double num1;
    double num2;
    double res;
    for (string::iterator it = postfx.begin(); it != postfx.end(); it++)
    {
        if (isOperand(*it))
            doubleStack.push((*it)-'0');

        if (isOperator(*it))
		{
            num1 = doubleStack.pop();
            num2 = doubleStack.pop();
            switch (*it)
            {
            case '+':
                res = num2 + num1;
                break;
            case '-':
                res = num2 - num1;
                break;
            case '/':
                res = num2 / num1;
                break;
            case '*':
                res = num2 * num1;
                break;
            }
            doubleStack.push(res);
		}
    }
    res = doubleStack.pop();
    return res ;
}