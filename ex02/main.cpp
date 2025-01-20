/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:45:59 by jmartos-          #+#    #+#             */
/*   Updated: 2025/01/20 14:35:23 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    Funciones mas usadas en los "stacks":

        - example.push(): Agrega un objeto al final del stack.
        - example.pop(): Elimina el ultimo objeto del stack.
        - example.top(): Devuelve el ultimo objeto del stack.
        - example.size(): Devuelve el tamaño del stack.
        - example.empty(): Devuelve si el stack esta vacio o no.

*/

/* (main copiado del subject y personalizado para mas aclaracion) */
#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Size is " << mstack.size() << std::endl;
    std::cout << "The last number in stack is " << mstack.top() << std::endl;
    std::cout << "Deleting the last one!" << std::endl;
    mstack.pop();
    std::cout << "New size is" << mstack.size() << std::endl;
    std::cout << "So now the last and only is " << mstack.top() << std::endl;
    
    std::cout << "Now we insert new numbers!" << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    MutantStack<int>::iterator itStart = mstack.begin();
    MutantStack<int>::iterator itEnd = mstack.end();
    
    std::cout << "The new iterator 'itStart' is pointing to " << *itStart << std::endl;
    std::cout << "The new iterator 'itEnd' is pointing to " << *itEnd << std::endl;
    
    ++itStart;
    --itStart;
    
    while (itStart != itEnd)
    {
        std::cout << *itStart << std::endl;
        ++itStart;
    }
    
    std::stack<int> s(mstack);

    std::cout << "The new stack 's' should have the same like 'mstack' but without iterators." << std::endl;
    std::cout << "The last number in 's' stack is " << s.top() << std::endl;
    std::cout << "The size of 's' stack is " << s.size() << std::endl;
    
    return 0;
}
