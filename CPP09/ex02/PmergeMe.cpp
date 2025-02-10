/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/10 15:27:09 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _v(), _d()
{
    std::cout << "[ Default constructor called! ]" << std::endl;
}

PmergeMe::~PmergeMe()
{
    std::cout << "[ Destructor called! ]" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy) : _v(copy._v), _d(copy._d)
{
    std::cout << "[ Copy constructor called! ]" << std::endl;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
    std::cout << "[ Overload assignation operator called! ]" << std::endl;
    if (this != &src) {
        this->_v = src._v;
        this->_d = src._d;
    }
    else {
        std::cout << "[ Same info. Copy abort! ]" << std::endl;
    }
    return (*this);
}

std::string PmergeMe::itoa(int number) {
    std::stringstream ascii;
    ascii << number;
    return ascii.str();
}

int PmergeMe::errorControl(int ac, char **av)
{
    if (ac < 3) {
        std::cout << "ERROR" << std::endl;
        return 1;
    }
    for (int i = 1; i < ac; i++) {
        for (int j = 0; av[i][j]; j++) {
            if (av[i][j] < '0' || av[i][j] > '9') {
                std::cout << "ERROR" << std::endl;
                return 1;
            }
        }
    }
    return 0;
}

void PmergeMe::makePairs(std::vector<std::pair<int, int> > &v, std::deque<std::pair<int, int> > &d)
{
    std::cout << std::endl;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].first > v[i].second) {
            std::pair<int, int> tmp(v[i].second, v[i].first);
            d.push_back(tmp);
        }
        else {
            d.push_back(v[i]);
        }
    }
}

void PmergeMe::separate(std::deque<std::pair<int, int> > &d)
{
    for (size_t i = 0; i < d.size(); i++) {
        if (d[i].first < d[i].second) {
            _v.push_back(d[i].first);
            _d.push_back(d[i].second);
        } else {
            _v.push_back(d[i].second);
            _d.push_back(d[i].first);
        }
    }
}

void PmergeMe::orderVector(containerV &_v)
{
    for (size_t i = 0; i < _v.size(); i++)
    {
        for (size_t j = i + 1; j < _v.size(); j++)
        {
            if (_v[i] > _v[j]) {
                // Intercambiar los elementos
                int temp = _v[i];
                _v[i] = _v[j];
                _v[j] = temp;
            }
        }
    }
    for (size_t i = 0; i < _v.size(); i++) {
        std::cout << "-" << _v[i];
    }
}

void PmergeMe::orderDeque(containerD &_d)
{
    for (size_t i = 0; i < _d.size(); i++)
    {
        for (size_t j = i + 1; j < _d.size(); j++)
        {
            if (_d[i] > _d[j]) {
                // Intercambiar los elementos
                int temp = _d[i];
                _d[i] = _d[j];
                _d[j] = temp;
            }
        }
    }
    for (size_t i = 0; i < _d.size(); i++) {
        std::cout << "+" << _d[i];
    }
}

void PmergeMe::printOrder(std::string last) {
    std::vector<int> combined(_v.begin(), _v.end());
    combined.insert(combined.end(), _d.begin(), _d.end());
    std::sort(combined.begin(), combined.end());
    for (size_t i = 0; i < combined.size(); i++) {
        std::cout << " " << combined[i];
    }
    if (last != "")
        std::cout << " " << last;
}

void PmergeMe::fillContainers(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        _v.push_back(std::atoi(av[i]));
        _d.push_back(std::atoi(av[i]));
    }    
    std::vector<std::pair<int, int> > v;    // AQUI GUARDAREMOS LA LISTA DE PARES DESORDENADA.
    std::deque<std::pair<int, int> > d;     // AQUI GUARDAREMOS LA LISTA DE PARES ORDENADA.
    std::string last = "";                  // AQUI GUARDAREMOS EL ULTIMO ELEMENTO SI EXISTE.
    for (int i = 1; i < ac; i += 2) {
        if (i + 1 < ac) {
            v.push_back(std::make_pair(_v[i - 1], _v[i]));
        } else {
            last = itoa(_v[i - 1]);
            break;
        }
    }
    // COMPROBACION QUE SE HAN RELLENADO BIEN EL CONTENEDOR 'V' DE PARES, EL DESORDENADO.
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << "(" << v[i].first << " - " << v[i].second << ")";
    }
    // ORDENADOMOS EL CONTENEDOR 'V' E INSERTAMOS LOS CAMBIO EN EL 'D'.
    makePairs(v, d);
    // COMPROBACION QUE SE HAN RELLENADO BIEN EL CONTENEDOR 'D' DE PARES, ORDENADO DE '-' A '+'.
    for (size_t i = 0; i < d.size(); i++) {
        std::cout << "(" << d[i].first << " - " << d[i].second << ")";
    }
    std::cout << std::endl;
    // BORRAMOS LA TOTALIDAD DE LOS ELEMENTOS DE LOS CONTENEDORES DE LAS CLASES PRIVADAS.
    for (int i = 1; i < ac; i++) {
        _v.pop_back();
        _d.pop_back();
    }
    // SEPARAMOS LOS ELEMENTOS GRANDES DE LOS PEQUEÑOS PARA METERLOS EN LA CLASE PRIVADA
    separate(d);
    // COMPROBACION QUE SE HAN RELLENADO BIEN EL CONTENEDOR PRIVADO '_V' CON LOS MENORES.
    for (size_t i = 0; i < _v.size(); i++) {
        std::cout << "-(" << _v[i] << ")";
    }
    std::cout << std::endl;
    // COMPROBACION QUE SE HAN RELLENADO BIEN EL CONTENEDOR PRIVADO '_D' CON LOS MAYORES.
    for (size_t i = 0; i < _d.size(); i++) {
        std::cout << "+(" << _d[i] << ")";
    }
    std::cout << std::endl;
    // ORDENAMOS LOS CONTENEDORES PRIVADOS '_V' Y '_D' Y LOS MOSTRAMOS, AL IGUAL QUE LAST (SI EXISTE).
    orderVector(_v);
    std::cout << std::endl;
    orderDeque(_d);
    std::cout << std::endl;
    printOrder(last);
    std::cout << std::endl;
}