/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numsize.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			numsize(int number)
{
	int		size;

	size = 1;
	while (number >= 10)
	{
		number = number / 10;
		size++;
	}
	return (size);
}
