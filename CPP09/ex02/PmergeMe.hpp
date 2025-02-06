/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:01:55 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/06 17:28:00 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <list>

class PmergeMe
{
    /* Alias para el container (simple ahorro gramatical para el .hpp y .cpp). */
    typedef std::vector<long int> containerV;
    typedef std::list<long int> containerL;
    /* Atributos privados. */
    private:
        containerV _v;
        containerL _l;
    /* Atributos publicos. */
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &src);
        void fillV(int ac, char **av);
        
};