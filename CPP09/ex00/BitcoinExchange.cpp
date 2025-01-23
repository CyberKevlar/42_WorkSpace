/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/23 13:58:01 by jmartos-         ###   ########.fr       */
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

/* Getter. */
BitcoinExchange::container BitcoinExchange::getter() {
    return _storage;
}

/* Setter. */
void BitcoinExchange::setter(std::string &date, double &value) {
    _storage[date] = value;
}

void BitcoinExchange::reading(std::string inputFile) {
    std::ifstream file;
    file.open(inputFile.c_str());
    if (!file) {
        std::cout << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    std::string date;
    double value;
    while (std::getline(file, line)) {
        std::istringstream new_line(line);
        if (std::getline(new_line, date, '|')) {
            new_line >> value;
            setter(date, value);
        }
        //std::cout << date << "| " << value << std::endl;    // DEBUG PARA COMPROBAR QUE SE ESTAN LEYENDO BIEN LAS LINEAS.
    }
}

void BitcoinExchange::processing(std::string inputCsv) {
    std::ifstream csv;
    csv.open(inputCsv.c_str());
    if (!csv) {
        std::cout << "Error: could not open csv." << std::endl;
        return ;
    }
    //ME HE QUEDADO POR AQUI!!!
    auto firstEntry = _storage.begin();
    std::string firstDate = firstEntry->first;
    double firstValue = firstEntry->second;
    
    return ;
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