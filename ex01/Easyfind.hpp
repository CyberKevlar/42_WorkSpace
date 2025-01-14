/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:47:06 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/14 11:34:55 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>

template <typename T>

class Integers {
    private:
        std::vector<T> _numbers;                    // RECORDEMOS: UN VECTOR ES UN ARRAY DINAMICO.
    public:
        Integers();                                 // RECORDEMOS: CONSTRUCTOR (OBLIGATORIO).
        Integers(const Integers &src);              // RECORDEMOS: CONSTRUCTOR DE COPIA (OBLIGATORIO).
        ~Integers();                                // RECORDEMOS: DESTRUCTOR (OBLIGATORIO).
        Integers &operator=(const Integers &src);   // RECORDEMOS: SOBRECARGA DEL OPERADOR DE ASIGNACION (OBLIGATORIO).
}

#include "Easyfind.tpp"                             // TEMPLATES: PLANTILLA DE FUNCIONES DE CLASE.
                                                    //  EL ARCHIVO DE LOS TEMPLATES SE INCLUYEN AL FINAL DEL ARCHIVO ".hpp",
                                                    //  YA QUE CONTENDRAN LA IMPLEMENTACION DE LAS FUNCIONES DE LA CLASE Y
                                                    //  ASI NOS AHORRAMOS EL PONERLAS AQUI.