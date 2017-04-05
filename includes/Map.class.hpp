/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <curses.h>
# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define MAGENTA 5
# define CYAN 6
# define WHITE 7

class Map
{
	public:
		Map(void);
		Map(int width, int height);
		Map(Map const & src);
		~Map(void);

		Map & operator=(Map const & rhs);

		int			getWidth(void) const;
		int			getHeight(void) const;
		int			getX(void) const;
		int			getY(void) const;
		WINDOW		*getWin(void) const;

	private:
		int			_width;
		int			_height;
		int			_x;
		int			_y;
		WINDOW		*_win;
};

#endif
