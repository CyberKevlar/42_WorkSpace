/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:12:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/06 17:28:06 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _v(), _l()
{
    std::cout << "[ Default constructor called! ]" << std::endl;
}

PmergeMe::~PmergeMe()
{
    std::cout << "[ Destructor called! ]" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &copy) : _v(copy._v), _l(copy._l)
{
    std::cout << "[ Copy constructor called! ]" << std::endl;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
    std::cout << "[ Overload assignation operator called! ]" << std::endl;
    if (this != &src) {
        this->_v = src._v;
        this->_l = src._l;
    }
    else {
        std::cout << "[ Same info. Copy abort! ]" << std::endl;
    }
    return (*this);
}

PmergeMe PmergeMe::fillV(int ac, char **av)
{
    
}