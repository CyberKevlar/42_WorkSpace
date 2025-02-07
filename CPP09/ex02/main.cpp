/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:01:52 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/07 11:07:35 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    PmergeMe p;
    if (p.errorControl(ac, av)) {
        std::cout << "ERROR" << std::endl;
        return 0;
    }
    p.fillNumbers(ac, av);
    return (0);
}