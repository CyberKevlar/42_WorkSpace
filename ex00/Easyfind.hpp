/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:47:06 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/14 15:26:57 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template <typename T>
typename T::iterator easyfind(T &container, int number);

class NotFoundException: public std::exception 
{
	public:
		virtual char const	*what() const throw();
};

#include "Easyfind.tpp"