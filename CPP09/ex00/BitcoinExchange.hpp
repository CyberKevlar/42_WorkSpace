/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:12 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/03 19:08:31 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream> 
#include <string>
#include <map>          // 'std::map' lo usaremos para los contenedores.
#include <fstream>      // 'std::ifstream' lo usaremos para leer archivos completos.
#include <sstream>      // 'std::istringstream' lo usaremos para leer lineas de archivos abiertos.
#include <ctime>        // lo usaremos para almacenar la fecha de los valores leidos.
#include <cstring>      // 'memset'.

class BitcoinExchange
{
    /* Alias para el container (simple ahorro gramatical para el .hpp y .cpp). */
    typedef std::map<std::string, double> container;
    /* Atributos privados. */
    private:
        container _storage;
    /* Atributos publicos. */
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &src);

        container getter();
        void setter(std::string &date, double &value);
        void reading(void);
        void processing(std::string input);
        int parseDate(const std::string &date, int &year, int &month, int &day);
        
        class NegativeNumberException : public std::exception {
            public:
                virtual const char	*what() const throw();
        };
        class BadDateException : public std::exception {
            public:
                virtual const char	*what() const throw();
        };
        class LongNumberException : public std::exception {
            public:
                virtual const char	*what() const throw();
        };
};