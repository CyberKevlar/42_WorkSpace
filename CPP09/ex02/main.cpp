/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:01:52 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/06 17:27:39 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cout << "ERROR" << std::endl;
        return (0);
    }
    for (int i = 1; i < ac; i++) {
        for (int j = 0; av[i][j]; j++) {
            if (av[i][j] < '0' || av[i][j] > '9') {
                std::cout << "ERROR" << std::endl;
                return (0);
            }
        }
    }
    PmergeMe p;
    p.fillV(ac, av);
    std::cout << "Before: ";
    for (int i = 1; i < ac; i++) {
        std::cout << " " << av[i];
    }
    std::cout << std::endl;
    std::cout << "After: ";
    for (int i = 1; i < ac; i++) {
        std::cout << " " << av[i];
    }
    std::cout << std::endl;
    return (0);
}