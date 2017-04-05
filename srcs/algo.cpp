/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:43:02 by rcherik           #+#    #+#             */
/*   Updated: 2016/02/09 16:48:16 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include <iostream>
#include <queue>
#include <map>
#include "Node.class.hpp"
#include "Puzzle.class.hpp"
#include <unistd.h>

typedef std::priority_queue<Node, std::vector<Node *>, Node>	t_nodepq;

void		free_open_set(t_nodepq & open_set)
{
	while (!open_set.empty())
	{
		delete open_set.top();
		open_set.pop();
	}
}

Node		*algo(Puzzle & puzzle, unsigned int *c_time, unsigned int *c_size)
{
	t_nodepq					open_set;
	std::map<t_matrix, char>	close_set;
	std::vector<Node *>			moves;
	Node						*start;
	Node						*lowest_cost;

	start = new Node(puzzle.getFilePuzzle(), 0, NULL, puzzle.getEndPuzzle(), puzzle.getHer());
	open_set.push(start);
	while (!open_set.empty())
	{
		lowest_cost = open_set.top();
		open_set.pop();
		if (lowest_cost->get_state() == puzzle.getEndPuzzle())
			return (lowest_cost);
		close_set[lowest_cost->get_state()] = 'a';
		lowest_cost->get_moves(moves, puzzle.getEndPuzzle(), puzzle.getHer());
		while (!moves.empty())
		{
			if (close_set[moves.back()->get_state()] != 'a')
			{
				moves.back()->set_prev(lowest_cost);
				open_set.push(moves.back());
				*c_time += 1;
			}
			else
				delete moves.back();
			moves.pop_back();
		}
		*c_size = open_set.size() + close_set.size() > *c_size ? open_set.size() + close_set.size() : *c_size;
	}
	return (NULL);
}
