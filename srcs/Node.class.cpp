/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 15:25:08 by rcherik           #+#    #+#             */
/*   Updated: 2016/02/12 18:18:57 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.class.hpp"

Node::Node(void)
{
	this->_cost = -1;
}

Node::Node(t_matrix state, unsigned int nb_move, Node *prev_state, t_matrix goal, int h):
	_state(state),
	_nb_move(nb_move),
	_prev_state(prev_state)
{
	this->_calc_cost(goal, h);
	this->_next_state = NULL;
}

Node::~Node(void) {}

std::pair<int, int>		Node::_get_pos(t_matrix goal, int elem)
{
	std::pair <int, int>	coords;
	int						x;

	for (int y = 0; y < (int)goal.size(); y++)
	{
		if ((x = std::distance(goal[y].begin(), std::find(goal[y].begin(), goal[y].end(), elem))) != (int)goal.size())
		{
				coords = std::make_pair(y, x);
				return (coords);
		}
	}
	return (coords);
}

void								Node::_manhattan(t_matrix goal)
{
	std::pair<int, int>		goal_coords;

	for (int y = 0; y < (int)this->_state.size(); y++)
	{
		for (int x = 0; x < (int)this->_state[y].size(); x++)
		{
			if (this->_state[y][x] != 0)
			{
				goal_coords = this->_get_pos(goal, this->_state[y][x]);
				this->_cost += abs(y - goal_coords.first) + abs(x - goal_coords.second);
			}
		}
	}
}

void								Node::_gaschnig(t_matrix goal)
{
	t_matrix				m = this->_state;
	std::pair<int, int>		c;
	std::pair<int, int>		c2;
	int						i;
	int						j;
	bool					breaked;
	int		t = 0;

	while (m != goal)
	{
		c = this->_get_pos(m, 0);
		if (!goal[c.first][c.second])
		{
			breaked = false;
			i = 0;
			while (i < (int)m.size())
			{
				j = 0;
				while (j < (int)m.size())
				{
					if (m[i][j] && goal[i][j] && m[i][j] != goal[i][j])
					{
						m[c.first][c.second] = m[i][j];
						m[i][j] = 0;
						this->_cost++;
						breaked = true;
						break ;
					}
					j++;
				}
				if (breaked)
					break ;
				i++;
			}
		}
		else
		{
			c2 = this->_get_pos(m, goal[c.first][c.second]);
			m[c.first][c.second] = m[c2.first][c2.second];
			m[c2.first][c2.second] = 0;
			this->_cost++;
		}
		if (t == 300)
		{
			printPuzzle(this->_state);
			printPuzzle(m);
			exit(0);
		}
		t++;
	}
}

void								Node::_hamming(t_matrix goal)
{
	for (unsigned int y = 0; y < this->_state.size(); y++)
	{
		for (unsigned int x = 0; x < this->_state[y].size(); x++)
		{
			if (this->_state[y][x] != 0 && goal[y][x] != this->_state[y][x])
					this->_cost++;
		}
	}
}

void								Node::_toorc(t_matrix goal)
{
	std::pair<int, int>		goal_coords;

	for (int y = 0; y < (int)this->_state.size(); y++)
	{
		for (int x = 0; x < (int)this->_state[y].size(); x++)
		{
			if (this->_state[y][x] != 0 && goal[y][x] != this->_state[y][x])
			{
				goal_coords = this->_get_pos(goal, this->_state[y][x]);
				if (y != goal_coords.first)
					this->_cost += 1;
				if (x != goal_coords.second)
					this->_cost += 1;
			}
		}
	}
}

void								Node::_calc_cost(t_matrix goal, int h)
{
	this->_cost = 0;
	if	(h == 2)
		this->_toorc(goal);
	else if	(h == 3)
		this->_hamming(goal);
	else if	(h == 4)
		this->_gaschnig(goal);
	else
		this->_manhattan(goal);
}

t_matrix									Node::get_state(void) const
{
	return this->_state;
}

int											Node::get_cost(void) const
{
	return this->_cost;
}

Node										*Node::get_prev_state(void)
{
	return this->_prev_state;
}

Node										*Node::get_next_state(void)
{
	return this->_next_state;
}

int											Node::get_nb_moves(void) const
{
	return this->_nb_move;
}

void										Node::print_state(void) const
{
	int		total_size;
	int		n;

	total_size = this->_state.size() * this->_state.size();
	total_size = numsize(total_size);
	for (size_t i = 0; i < this->_state.size(); i++)
	{
		for (size_t j = 0; j < this->_state[i].size(); j++)
		{
			n = numsize(this->_state[i][j]);
			std::cout << this->_state[i][j] << " ";
			for (int z = 0; z < total_size - n; z++)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool			Node::operator()(const Node *left, const Node *right)
{
	return (left->get_cost() > right->get_cost());  
}

t_matrix									Node::_copy_matrix(void)
{
	int		len = this->_state.size();
	t_matrix	ret(len, std::vector<int>(len));

	for (int y = 0; y < len; y++)
	{
		for (int x = 0; x < len; x++)
			ret[y][x] = this->_state[y][x];
	}
	return (ret);
}

void		Node::get_moves(std::vector<Node *> & ret, t_matrix goal, int h)
{
	int						len;
	std::pair<int, int>		goal_coords;
	t_matrix				tmp;

	len = this->_state.size();
	goal_coords = this->_get_pos(this->_state, 0);
	if (goal_coords.first - 1 >= 0)
	{
		tmp = this->_copy_matrix();
		tmp[goal_coords.first][goal_coords.second] = tmp[goal_coords.first - 1][goal_coords.second];
		tmp[goal_coords.first - 1][goal_coords.second] = 0;
		ret.push_back(new Node(tmp, this->_nb_move + 1, this, goal, h));
	}
	if (goal_coords.second + 1 < len)
	{
		tmp = this->_copy_matrix();
		tmp[goal_coords.first][goal_coords.second] = tmp[goal_coords.first][goal_coords.second + 1];
		tmp[goal_coords.first][goal_coords.second + 1] = 0;
		ret.push_back(new Node(tmp, this->_nb_move + 1, this, goal, h));
	}
	if (goal_coords.first + 1 < len)
	{
		tmp = this->_copy_matrix();
		tmp[goal_coords.first][goal_coords.second] = tmp[goal_coords.first + 1][goal_coords.second];
		tmp[goal_coords.first + 1][goal_coords.second] = 0;
		ret.push_back(new Node(tmp, this->_nb_move + 1, this, goal, h));
	}
	if (goal_coords.second - 1 >= 0)
	{
		tmp = this->_copy_matrix();
		tmp[goal_coords.first][goal_coords.second] = tmp[goal_coords.first][goal_coords.second - 1];
		tmp[goal_coords.first][goal_coords.second - 1] = 0;
		ret.push_back(new Node(tmp, this->_nb_move + 1, this, goal, h));
	}
}

void	Node::set_next(Node *node)
{
	this->_next_state = node;
}
void	Node::set_prev(Node *node)
{
	this->_prev_state = node;
}
