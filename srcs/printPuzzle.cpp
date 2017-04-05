/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printPuzzle.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 19:49:28 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/12 17:54:26 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

void				printPuzzle(t_matrix container)
{
	t_matrix::iterator		it = container.begin();
	int						i;
	int						size;

	size = numsize(container.size() * container.size());
	while (it != container.end())
	{
		t_matrixLine::iterator		it2 = (*it).begin();
		while (it2 != (*it).end())
		{
			std::cout << (*it2) << " ";
			i = 0;
			while (i < size - numsize(*it2))
			{
				std::cout << " ";
				i++;
			}
			it2++;
		}
		std::cout << std::endl;
		it++;
	}
	std::cout << std::endl;
}
