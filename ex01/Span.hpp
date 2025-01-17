/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:47:06 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/17 14:12:19 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

class Span {
    private:
        unsigned int _size;                                         // TAMAÑO DEL VECTOR (PONEMOS UNSIGNED INT PARA LA ENTRADA DE N_ EN EL CONSTRUCTOR).
        unsigned int _position;                                     // POSICION ACTUAL DEL ITERADOR (PONEMOS UNSIGNED INT PARA QUE NO DE PROBLEMAS AL COMPARARLO CON SIZE).
        std::vector<int> _storage;                                  // VECTOR DE ALMACENAMIENTO DE NUMEROS.
    public:                 
        Span();                                                     // CONSTRUCTOR (OBLIGATORIO).
        Span(unsigned int N_);                  
        Span(const Span &src);                                      // CONSTRUCTOR DE COPIA (OBLIGATORIO).
        ~Span();                                                    // DESTRUCTOR (OBLIGATORIO).
        Span    &operator=(const Span &src);                        // SOBRECARGA DEL OPERADOR DE ASIGNACION (OBLIGATORIO).
        void    addNumber(int number_);
        int     shortestSpan();                                     // ESTA FUNCION CALCULA LA DISTANCIA ENTRE LOS DOS NUMEROS MAS CERCANOS.
        int     longestSpan();                                      // ESTA FUNCION CALCULA LA DISTANCIA ENTRE EL NUMERO MAS PEQUEÑO Y EL MAS GRANDE.
        class   StorageFullException: public std::exception {
            public:
                virtual const char *what() const throw();
        };
        class   StorageEmptyException: public std::exception {
            public:
                virtual const char *what() const throw();
        };
};