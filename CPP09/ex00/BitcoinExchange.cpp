/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/03 19:22:58 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _storage()
{
    std::cout << "[ Default constructor called! ]" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "[ Destructor called! ]" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _storage(copy._storage)
{
    std::cout << "[ Copy constructor called! ]" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
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
BitcoinExchange::container BitcoinExchange::getter()
{
    return _storage;
}

/* Setter. */
void BitcoinExchange::setter(std::string &date, double &value)
{
    _storage[date] = value;
}

/* Funcion para parsear la fecha. */
int BitcoinExchange::parseDate(const std::string &line, int &year, int &month, int &day)
{
    if (sscanf(line.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
        std::cout << "Error: bad input date." << std::endl;
        return 1;
    }
    else if (year < 0 || month < 0 || day < 0 || line.find('-') == std::string::npos) {
        std::cout << "Error: not a positive number." << year << "-" << month << "-" << day << std::endl;
        return 1;
    }
    else if (year > 9999 || month > 12 || day > 31) {
        std::cout << "Error: too large number." << std::endl;
        return 1;
    }
    return 0;
}

/* Funcion para leer el archivo '.csv' y almacenar sus valores en el contenedor tipo 'map' de la clase. */
void BitcoinExchange::reading(void)
{
    std::ifstream csv;
    csv.open("data.csv");
    if (!csv) {
        std::cout << "Error: could not open 'data.csv' file" << std::endl;
        return ;
    }
    std::string line;
    std::string date;
    double value;
    while (std::getline(csv, line)) {               // Leemos el archivo usando 'getline' y almacenamos el contenido en 'line'.
        std::istringstream new_line(line);          // Creamos un nuevo objeto tipo 'istringstream' a partir de cada linea leida. Con este objeto podremos extraer datos de los valores de la linea leida.
        if (std::getline(new_line, date, ',')) {    // Si la condicion de usar 'getline' para leer desde 'new_line' y almacenar en 'date' usando la pipe como delimitador es OK... 
            new_line >> value;                      // ... entonces leemos el valor de 'new_line' y lo almacenamos en 'value'.
            setter(date, value);
        }
        //std::cout << "DEBUG MODE * " << date << " | " << value << std::endl;    // DEBUG!!!
    }
}

/* Funcion para comparar los valores de '_storage' y del 'input'. */
void BitcoinExchange::processing(std::string input) {
    std::ifstream file;
    file.open(input.c_str());
    if (!file) {
        std::cout << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    while(std::getline(file, line, ',')) {
        std::istringstream new_line(line);
        std::string date;
        double value;
        if (std::getline(new_line, date, ',')) {
            new_line >> value;
            if (new_line.fail() || value < 0) {
                std::cout << "Error: invalid value in line." << std::endl;
                continue ;
            }
            int year, month, day;
            try {
                parseDate(line, year, month, day);
                std::cout << year << " | " << month << " | " << day << std::endl;    // DEBUG!!!
            }
            catch (const BadDateException &e) {
                std::cout << e.what() << std::endl;
            }
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
    return ("Error: too large number.");
}