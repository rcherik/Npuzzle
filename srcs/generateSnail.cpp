/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateSnail.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 21:15:58 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/05 13:32:18 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"

static void	one_two_snail(t_matrix & lst, int *y, int *x, int *num, int size)
{
	int		i;
	int		j;

	i = *y;
	j = *x;
	while (j < size)
	{
		lst[i][j] = *num;
		*num += 1;
		j++;
	}
	j--;
	i++;
	while (i < size)
	{
		lst[i][j] = *num;
		*num += 1;
		i++;
	}
	*y = --i;
	*x = --j;
}

static void	three_four_snail(t_matrix & lst, int *y, int *x, int *num)
{
	int		i;
	int		j;

	i = *y;
	j = *x;
	while (j >= 0 && lst[i][j] == 0)
	{
		lst[i][j] = *num;
		*num += 1;
		j--;
	}
	j++;
	i--;
	while (i >= 0 && lst[i][j] == 0)
	{
		lst[i][j] = *num;
		*num += 1;
		i--;
	}
	*y = ++i;
	*x = ++j;
}

static void		replace_last(t_matrix & lst, int size, int num)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (lst[i][j] == num)
			{
				lst[i][j] = 0;
				return ;
			}
			j++;
		}
		i++;
	}
}

t_matrix		generateSnail(int size)
{
	int					index;
	int					i;
	int					j;
	int					num;
	int					snailSize;
	t_matrix			lst(size, t_matrixLine(size));

	i = 0;
	j = 0;
	num = 1;
	snailSize = size;
	index = 0;
	while (index < size - 2)
	{
		one_two_snail(lst, &i, &j, &num, snailSize);
		three_four_snail(lst, &i, &j, &num);
		snailSize -= 1;
		index += 1;
	}
	replace_last(lst, size, size * size);
	return (lst);
}
