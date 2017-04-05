/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 15:17:21 by rcherik           #+#    #+#             */
/*   Updated: 2016/02/12 16:27:45 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include "n_puzzle.hpp"
# include <utility>
# include <iostream>
# include <stdlib.h>
# include <math.h>
# include <queue>

class	Node;

class	Node
{
	public:
		Node(t_matrix state, unsigned int nb_move, Node *prev_state, t_matrix goal, int h);
		~Node(void);

		t_matrix				get_state(void) const;
		Node					*get_prev_state(void);
		Node					*get_next_state(void);
		void					get_moves(std::vector<Node *> &ret, t_matrix goal, int h);
		int						get_nb_moves(void) const;
		int						get_cost(void) const;
		void					print_state(void) const;
		bool					operator()(const Node *left, const Node *right);
		void					set_prev(Node *node);
		void					set_next(Node *node);
		Node(void);

	private:
		void					_calc_cost(t_matrix goal, int h);
		std::pair<int, int>		_get_pos(t_matrix, int elem);
		void					_gaschnig(t_matrix goal);
		void					_manhattan(t_matrix goal);
		void					_hamming(t_matrix goal);
		void					_toorc(t_matrix goal);
		t_matrix				_copy_matrix(void);
		t_matrix				_state;
		int						_nb_move;
		Node					*_prev_state;
		Node					*_next_state;
		int						_cost;
};

#endif
