/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:47:06 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/13 19:26:20 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Easyfind.tpp"
#include <iostream>
#include <algorithm>

template <typename T>

class Integers {
    private:
        std::vector<T> _numbers;                    // RECORDEMOS: UN VECTOR ES UN ARRAY DINAMICO.
    public:
        Integers();                                 // RECORDEMOS: UN CONSTRUCTOR ES OBLIGATORIO EN LA CLASE CANONICA ORTODOXA.
        Integers(const Integers &src);              // RECORDEMOS: UN CONSTRUCTOR DE COPIA ES OBLIGATORIO EN LA CLASE CANONICA ORTODOXA.
        ~Integers();                                // RECORDEMOS: UN DESTRUCTOR ES OBLIGATORIO EN LA CLASE CANONICA ORTODOXA.
        Integers &operator=(const Integers &src);   // RECORDEMOS: UN OPERADOR DE SOBRECARGA DE ASIGNACION ES OBLIGATORIO EN LA CLASE CANONICA ORTODOXA.
}