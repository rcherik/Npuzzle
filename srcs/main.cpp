/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:43:48 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/16 16:27:33 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.class.hpp"
#include "n_puzzle.hpp"
#include <unistd.h>
#include <csignal>
#include <time.h>

void	print_path(Node *path)
{
	Node	*l;

	l = path;
	while (l)
	{
		l->print_state();
		l = l->get_next_state();
	}
}

static void	graph_ncurses(Puzzle puzzle, Node *l, unsigned int c_time,
									unsigned int c_size, float total_time)
{
	int				index;
	int				key;
	long long		speed;
	Node			*path;

	path = l;
	index = 0;
	puzzle.setCurses();
	while (!puzzle.getFinished())
	{
		key = wgetch(puzzle.getMap().getWin());
		puzzle.parseKey(key, &path, &index);
		wclear(puzzle.getMap().getWin());
		puzzle.graphPuzzle(path->get_state());
		if (!puzzle.isPaused() && path->get_next_state())
		{
			path = path->get_next_state();
			index++;
			puzzle.printSolution(-1, -1, index, -1);
		}
		else if (path->get_next_state() == NULL)
		{
			puzzle.printSolution(c_time, c_size, index, total_time);
			puzzle.setSpeed(0);
		}
		else
			puzzle.printSolution(-1, -1, index, -1);
		wrefresh(puzzle.getMap().getWin());
		speed = 100000 + puzzle.getSpeed() < 30000 ? 30000 : 100000 + puzzle.getSpeed();
		usleep(speed);
	}
	puzzle.exitCurses();
}

static Node		*double_link(Node *path, int *nb_move)
{
	while (path->get_prev_state())
	{
		path->get_prev_state()->set_next(path);
		path = path->get_prev_state();
		*nb_move += 1;
	}
	return (path);
}

static void		free_path(Node *path)
{
	Node	*tmp;

	while (path)
	{
		tmp = path;
		path = path->get_next_state();
		delete tmp;
	}
}

int			main(int argc, char **argv)
{
	Puzzle			puzzle;
	Node			*path;
	int				nb_move = 0;
	unsigned int	c_time = 1;
	unsigned int	c_size = 0;
	float			total_time;

	std::srand(unsigned(time(0)));
	if (parseArgs(argc, argv, puzzle))
		return (1);
	const clock_t	begin_time = clock();
	path = algo(puzzle, &c_time, &c_size);
	total_time = (float)(clock() - begin_time) / CLOCKS_PER_SEC;
	path = double_link(path, &nb_move);
	if (puzzle.checkSum(G_OPT))
	{
		if (puzzle.checkSum(S_OPT))
			return (error("You must send a file to get a graphical ncurses output"));
		graph_ncurses(puzzle, path, c_time, c_size, total_time);
	}
	else
	{
		print_path(path);
		std::cout << "Number of moves: " << nb_move << std::endl;
		std::cout << "Complexity in time: " << c_time << std::endl;
		std::cout << "Complexity in size: " << c_size << std::endl;
		std::cout << "Calculation time: " << total_time << "s" << std::endl;
	}
	free_path(path);
	return (0);
}
