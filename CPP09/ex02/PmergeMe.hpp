/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartos- <jmartos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:01:55 by jmartos-          #+#    #+#             */
/*   Updated: 2025/02/10 15:14:06 by jmartos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>       // std::string y std::to_string
#include <cstdlib>      // std::atoi
#include <vector>       // std::vector<int> 
#include <deque>        // std::deque<int>
#include <utility>      // std::pair
#include <algorithm>    // std::sort
#include <sstream>      // std::stringstream

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
        std::string itoa(int number);
        int errorControl(int ac, char **av);
        void makePairs(std::vector<std::pair<int, int> > &v, std::deque<std::pair<int, int> > &d);
        void separate(std::deque<std::pair<int, int> > &d);
        void orderVector(containerV &_v);
        void orderDeque(containerD &_d);
        void printOrder(std::string last);
        void fillContainers(int ac, char **av);
};