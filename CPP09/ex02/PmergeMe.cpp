/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/07 16:21:38 by jmartos-         ###   ########.fr       */
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

void PmergeMe::fillPairs(std::vector<std::pair<int, int> > &v, std::deque<std::pair<int, int> > &d, int last)
{
    std::cout << "- Vector: ";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << "(" << v[i].first << " - " << v[i].second << ") ";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].first < v[i].second) {
            std::pair<int, int> tmp(v[i].second, v[i].first);
            d.push_back(tmp);
        }
        else {
            d.push_back(v[i]);
        }
    }
    std::cout << "- Deque: ";
    for (size_t i = 0; i < d.size(); i++) {
        std::cout << d[i].first << " " << d[i].second << " ";
    }
    std::cout << last << std::endl;
}

//void PmergeMe::mercheDeque(std::deque<int, int> &d)
//{
//        
//}

void PmergeMe::fillNumbers(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        _v.push_back(std::atoi(av[i]));
        _d.push_back(std::atoi(av[i]));
    }    
    std::vector<std::pair<int, int> > v;
    std::deque<std::pair<int, int> > d;
    int last = 0;
    for (int i = 1; i < ac; i += 2) {
        if (!_v[i]) {
            last = _v[i - 1];
            break ;
        }
        v.push_back(std::make_pair(_v[i - 1], _v[i]));
    }
    fillPairs(v, d, last);
    for (int i = 1; i < ac; i++) {
        _v.pop_back();
        _d.pop_back();
    }
    for (size_t i = 0; i < d.size(); i++) {
        _d.push_back(d[i].first);
        _d.push_back(d[i].second);
    }
    // ...
    //mercheDeque(_d);
}