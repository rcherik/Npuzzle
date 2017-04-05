/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.class.hpp"
#include <curses.h>

Map::Map(void)
{
	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

Map::Map(int width, int height) : _width(width), _height(height), _x(0),  _y(0)
{
	_win = newwin(_height, _width, _y, _x);
	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

Map::Map(Map const & src)
{
	*this = src;
}

Map::~Map(void)
{
}

int			Map::getWidth(void) const
{
	return this->_width;
}
int			Map::getHeight(void) const
{
	return this->_height;
}

int			Map::getX(void) const
{
	return this->_x;
}

int			Map::getY(void) const
{
	return this->_y;
}

WINDOW		*Map::getWin(void) const
{
	return this->_win;
}

Map &		Map::operator=(Map const & rhs)
{
	if (this != &rhs)
	{
		this->_width = rhs.getWidth();
		this->_height = rhs.getHeight();
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_win = rhs.getWin();
	}
	return *this;
}
