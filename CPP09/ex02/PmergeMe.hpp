/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:01:55 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/07 22:15:20 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>   // std::string
#include <cstdlib>  // std::atoi
#include <vector>
#include <deque>

class PmergeMe
{
    /* Alias para el container (simple ahorro gramatical para el .hpp y .cpp). */
    typedef std::vector<int> containerV;
    typedef std::deque<int> containerD;
    /* Atributos privados. */
    private:
        containerV _v;
        containerD _d;
    /* Atributos publicos. */
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &src);
        int errorControl(int ac, char **av);
        void fillPairs(std::vector<std::pair<int, int> > &v, std::deque<std::pair<int, int> > &d);
        void mercheDeque(std::deque<std::pair<int, int> > &d, int size);
        void fillContainers(int ac, char **av);
};