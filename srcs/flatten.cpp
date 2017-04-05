/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 17:31:18 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/08 19:02:51 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

void				print(std::string put)
{
	std::cout << put << std::endl;
}

void				print(int put)
{
	std::cout << put << std::endl;
}

void				print(t_matrixLine line)
{
	unsigned int		i;

	i = 0;
	while (i < line.size())
	{
		std::cout << "line[" << i << "] = " << line[i] << std::endl;
		i++;
	}
}

static void	one_two_snail(t_matrixLine & lst, t_matrix matrix, int *y, int *x, int size, int *n)
{
	int		i;
	int		j;
	int		z;
	int		total_size;

	total_size = matrix.size() * matrix.size();
	i = *y;
	j = *x;
	z = 0;
	while (*n < total_size && z < size)
	{
		lst[*n] = matrix[i][j];
		*n += 1;
		j++;
		z++;
	}
	z = 0;
	while (*n < total_size && z < size)
	{
		lst[*n] = matrix[i][j];
		*n += 1;
		i++;
		z++;
	}
	*y = i;
	*x = j;
}

static void	three_four_snail(t_matrixLine & lst, t_matrix matrix, int *y, int *x, int size, int *n)
{
	int		i;
	int		j;
	int		z;
	int		total_size;

	total_size = matrix.size() * matrix.size();
	i = *y;
	j = *x;
	z = 0;
	while (*n < total_size && z < size)
	{
		lst[*n] = matrix[i][j];
		*n += 1;
		j--;
		z++;
	}
	z = 0;
	while (*n < total_size && z < size)
	{
		lst[*n] = matrix[i][j];
		*n += 1;
		i--;
		z++;
	}
	*y = ++i;
	*x = ++j;
}

t_matrixLine		flatten(t_matrix matrix)
{
	int					index;
	int					i;
	int					j;
	int					snailSize;
	t_matrixLine		lst(matrix.size() * matrix.size());
	int					n;
	int					size;
	int					new_size;

	i = 0;
	j = 0;
	size = matrix.size();
	snailSize = size - 1;
	new_size = size;
	index = 0;
	n = 0;
	while (snailSize > 0)
	{
		one_two_snail(lst, matrix, &i, &j, snailSize, &n);
		three_four_snail(lst, matrix, &i, &j, snailSize, &n);
		new_size -= 2;
		snailSize = new_size - 1;
		index += 1;
	}
	if (snailSize == 0)
		lst[n] = matrix[i][j];
	return (lst);
}
