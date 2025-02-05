/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/05 18:57:30 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _calculator()
{
    std::cout << "[ Default constructor called! ]" << std::endl;
}

RPN::~RPN()
{
    std::cout << "[ Destructor called! ]" << std::endl;
}

RPN::RPN(const RPN &copy) : _calculator(copy._calculator)
{
    std::cout << "[ Copy constructor called! ]" << std::endl;
}

RPN &RPN::operator=(const RPN &src)
{
    std::cout << "[ Overload assignation operator called! ]" << std::endl;
    if (this != &src) {
        this->_calculator = src._calculator;
    }
    else {
        std::cout << "[ Same info. Copy abort! ]" << std::endl;
    }
    return (*this);
}

void RPN::parseInput(std::string input)
{
    int digits = 0;
    int size = input.size();
    int a;
    int b;
    for (int i = 0; i < size; i++) {
        if (!isdigit(input[i]) && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/') {
            std::cout << "ERROR: bad character." << std::endl;
            return ;
        }
    }
    for (size_t i = 0; i < input.size(); ++i)
    {
        if (isdigit(input[i]))
            digits++;
    }
    if (digits >= 10) {
        std::cout << "ERROR: too many numbers." << std::endl;
        return ;
    }
    digits = 0;
    for (int i = 0; i < size; i++)
    {
        if (input[i] == ' ')
            continue;
        if (isdigit(input[i])) {
            _calculator.push(input[i] - '0');
            digits++;
        }
        else if (input[i] == '+') {
            a = _calculator.top();
            _calculator.pop();
            b = _calculator.top();
            _calculator.pop();
            _calculator.push(a + b);
            digits--;
        }
        else if (input[i] == '-') {
            a = _calculator.top();
            _calculator.pop();
            b = _calculator.top();
            _calculator.pop();
            _calculator.push(b - a);
            digits--;
        }
        else if (input[i] == '*') {
            a = _calculator.top();
            _calculator.pop();
            b = _calculator.top();
            _calculator.pop();
            _calculator.push(a * b);
            digits--;
        }
        else if (input[i] == '/') {
            a = _calculator.top();
            _calculator.pop();
            b = _calculator.top();
            _calculator.pop();
            _calculator.push(b / a);
            digits--;
        }
    }
    if (digits != 1) {
        std::cout << "ERROR: result have too many numbers." << std::endl;
        return ;
    }
    std::cout << _calculator.top() << std::endl;
}