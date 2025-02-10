/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:01:52 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/10 19:37:13 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    PmergeMe p;
    if (p.errorControl(ac, av)) {
        return 0;
    }

    p.fillContainers(ac, av);

    gettimeofday(&end, NULL);
    //std de start
    //std de end

    return 0;
}