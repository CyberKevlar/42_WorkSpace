/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/04 16:50:15 by jmartos-         ###   ########.fr       */
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

void BitcoinExchange::setter(std::string &date, double &value)
{
    _storage[date] = value;
}

void BitcoinExchange::saveCSV(void)
{
    std::ifstream csv;
    csv.open("data.csv");
    if (!csv)
    {
        std::cout << "Error: there's no file to open." << std::endl;
        return ;
    }
    std::string line;
    std::string date;
    double value;
    while (std::getline(csv, line))                 // Leemos el archivo usando 'getline' y almacenamos el contenido en 'line'.
    {
        std::istringstream new_line(line);          // Creamos un nuevo objeto tipo 'istringstream' a partir de cada linea leida. Con este objeto podremos extraer datos de los valores de la linea leida.
        if (std::getline(new_line, date, ','))      // Si la condicion de usar 'getline' para leer desde 'new_line' y almacenar en 'date' usando la pipe como delimitador es OK... 
        {
            new_line >> value;                      // ... entonces leemos el valor de 'new_line' y lo almacenamos en 'value'.
            setter(date, value);                    // Por ultimo usamos el 'setter' y almacenamos los valores en el contenedor '_storage' de la parte privada de la clase.
        }
        //std::cout << std::fixed << std::setprecision(2) << date << " | " << value << std::endl;    // DEBUG!!!
    }
}

double BitcoinExchange::compare(std::string date, double value)
{
    for (container::iterator it = _storage.begin(); it != _storage.end(); it++)
    {
        if (it->first == date)
        {
            return (it->second * value);
        }
        else if (it->first > date)
        {
            if (it->first == _storage.begin()->first)
                return (-1);
            it--;
            return (it->second * value);
        }
    }
    return (-1);
}

void BitcoinExchange::checkInput(std::string input)
{
    saveCSV();
    std::ifstream file;
    file.open(input.c_str());
    if (!file) {
        std::cout << "Error: there's no file to open." << std::endl;
        return ;
    }
    std::string line;
    std::string date;
    double value;
    while(std::getline(file, line))
    {
        std::istringstream new_line(line);
        if (std::getline(new_line, date, '|'))
        {
            new_line >> value;
            
            double result = compare(date, value);
            
            std::cout << date << " | " << result << std::endl;
        }
    }
}
