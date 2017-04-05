/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:50:51 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/09 20:02:49 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_CLASS_HPP
# define PUZZLE_CLASS_HPP

# include "n_puzzle.hpp"
# include "Map.class.hpp"

class	Puzzle
{
	public:
		Puzzle(void);
		Puzzle(Puzzle const & src);
		~Puzzle(void);

		int				getSize(void) const;
		int				getSum(void) const;
		int				getHer(void) const;
		long long		getSpeed(void) const;
		std::string		getError(void) const;
		t_matrix &		getFilePuzzle(void);
		t_matrix &		getEndPuzzle(void);
		t_matrix &		getPuzzle(void);
		void			setSum(int sum);
		void			setSize(int size);
		void			setAlgo(char *algo);
		void			setSpeed(long long num);
		void			setPuzzle(char *filename);
		void			setError(std::string error);
		bool			isError(void) const;
		bool			checkSum(int opt);
		void			printDebug(std::string debug);
		void			debugPuzzle(std::string debug, t_matrix puzzle);
		void			fillPuzzle(std::list<std::string> file);
		void			checkIntegrity(t_matrix puzzle);
		bool			checkSolvable(t_matrix puzzle);
		t_matrixLine	getLineContent(std::string line, int size);

		/*
		** Graphical
		*/

		Map &			getMap(void);
		bool			getFinished(void) const;
		void			setMap(int w, int h);
		bool			isPaused(void) const;
		void			setCurses(void);
		void			exitCurses(void);
		void			parseKey(int key, Node **path, int *index);
		void			printBlock(int center_x, int center_y, int y, int x, int num, int size, int inter);
		void			printHelp(void);
		void			printSolution(int c_time, int c_size, int nb_moves, float total_time);
		void			graphPuzzle(t_matrix puzzle);

	private:
		bool			_isError;
		std::string		_error;
		int				_heur;
		std::string		_algo;
		int				_sum;
		int				_size;
		t_matrix		_puzzle;
		t_matrix		_endPuzzle;
		t_matrix		_filePuzzle;
		t_matrixLine	_dict;

		/*
		** Graphical
		*/

		Map				_map;
		bool			_finished;
		int				_x;
		int				_y;
		bool			_paused;
		bool			_help;
		long long		_speed;
};

#endif
