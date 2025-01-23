/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:10:17 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/23 13:44:28 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac , char **av)
{
	(void)av;
	if (ac != 2)
	{
		std::cout << "Error: there's no file to open." << std::endl;
		return 0;
	}
	char *csv = "data.csv";
	BitcoinExchange container;
	container.reading(av[1]);
	container.processing(csv);
	return 0;    
}