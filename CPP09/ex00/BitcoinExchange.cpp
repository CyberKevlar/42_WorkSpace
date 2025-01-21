/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/21 16:44:23 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _storage() {
    std::cout << "[ Default constructor called! ]" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {
    std::cout << "[ Destructor called! ]" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _storage(copy._storage) {
    std::cout << "[ Copy constructor called! ]" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src) {
    std::cout << "[ Overload assignation operator called! ]" << std::endl;
    if (this != &src) {
        this->_storage = src._storage;
    }
    else {
        std::cout << "[ Same info. Copy abort! ]" << std::endl;
    }
    return (*this);
}

void BitcoinExchange::setter(std::string &date, double &value) {
    _storage[date] = value;
}

void BitcoinExchange::reading(std::string csv) {
    std::ifstream file(csv);
    if (!file) {
        std::cout << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream new_line(line);
        std::string date;
        double value;
        if (std::getline(new_line, date, '|')) {
            new_line >> value;
            setter(date, value);
        }
    }
    
}

const char	*BitcoinExchange::NegativeNumberException::what() const throw() {
    return ("Error: not a positive number.");
}

const char	*BitcoinExchange::BadDateException::what() const throw() {
    return ("Error: bad input date.");
}

const char	*BitcoinExchange::LongNumberException::what() const throw() {
    return ("Error: too large a number.");
}