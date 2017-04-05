/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 19:10:24 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/12 18:45:05 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_HPP
# define N_PUZZLE_HPP

# include <curses.h>
# include <algorithm>
# include <string>
# include <sstream>
# include <fstream>
# include <vector>
# include <iostream>
# include <list>

# define F_OPT (2 << 0)
# define S_OPT (2 << 1)
# define A_OPT (2 << 2)
# define G_OPT (2 << 3)
# define D_OPT (2 << 4)
# define H_OPT (2 << 5)
# define O_OPT (2 << 6)

class Puzzle;

typedef std::vector< std::vector<int> >	t_matrix;
typedef std::vector<int>				t_matrixLine;

# include "Node.class.hpp"

class Node;

int							error(std::string error);
int							parseArgs(int argc, char **argv, Puzzle & puzzle);
int							numsize(int num);
std::vector<std::string> &	split(const std::string & s, char delim, std::vector<std::string> & elems);
std::vector<std::string>	split(const std::string & s, char delim);
void						printPuzzle(t_matrix container);
t_matrix					generateSnail(int size);
t_matrixLine				flatten(t_matrix matrix);
Node				*algo(Puzzle & puzzle, unsigned int *c_time, unsigned int *c_size);

#endif
