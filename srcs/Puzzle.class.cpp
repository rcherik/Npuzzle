/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 15:10:47 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/16 16:25:16 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.class.hpp"
#include "n_puzzle.hpp"

Puzzle::Puzzle(void)
{
	_sum = 0;
	_size = 0;
	_isError = false;
	_error = std::string();
	_heur = 1;
	_algo = std::string();
	_puzzle = t_matrix();
	_endPuzzle = t_matrix();
	_filePuzzle = t_matrix();
	_dict = t_matrixLine();
	_finished = false;
	_x = 0;
	_y = 0;
	_paused = true;
	_speed = 0;
	_help = false;
}

Puzzle::Puzzle(Puzzle const & src)
{
	*this = src;
}

Puzzle::~Puzzle(void)
{
}

t_matrix &			Puzzle::getFilePuzzle(void)
{
	return (this->_filePuzzle);
}

t_matrix &			Puzzle::getEndPuzzle(void)
{
	return (this->_endPuzzle);
}

t_matrix &			Puzzle::getPuzzle(void)
{
	return (this->_puzzle);
}

int					Puzzle::getSize(void) const
{
	return (this->_size);
}

long long			Puzzle::getSpeed(void) const
{
	return (this->_speed);
}

int					Puzzle::getHer(void) const
{
	return (this->_heur);
}

bool				Puzzle::isPaused(void) const
{
	return (this->_paused);
}

int					Puzzle::getSum(void) const
{
	return (this->_sum);
}

std::string			Puzzle::getError(void) const
{
	return (this->_error);
}

bool				Puzzle::isError(void) const
{
	return (this->_isError);
}

void				Puzzle::setSize(int size)
{
	if (size < 3)
		this->setError("Size too low");
	if (size > 500)
		this->setError("Size too high, you are going to wait years...");
	this->_size = size;
}

void				Puzzle::setSpeed(long long num)
{
	this->_speed = num;
}

void				Puzzle::setSum(int sum)
{
	this->_sum = sum;
}

void				Puzzle::setAlgo(char *algo)
{
	if (algo)
	{
		this->_algo = std::string(algo);
		std::transform(this->_algo.begin(), this->_algo.end(), this->_algo.begin(), (int (*)(int))std::tolower);
		if (!this->_algo.empty())
		{
			if (this->_algo == "manhattan")
				this->_heur = 1;
			else if (this->_algo == "toorc")
				this->_heur = 2;
			else if (this->_algo == "hamming")
				this->_heur = 3;
			else if (this->_algo == "gaschnig")
				this->_heur = 4;
			else if (this->_algo == "1")
				this->_heur = 1;
			else if (this->_algo == "2")
				this->_heur = 2;
			else if (this->_algo == "3")
				this->_heur = 3;
			else if (this->_algo == "4")
				this->_heur = 4;
			else
				this->setError("No such heuristic");
		}
	}
}

bool				Puzzle::checkSum(int opt)
{
	if ((this->_sum & opt))
		return (true);
	return (false);
}

void				Puzzle::setError(std::string error)
{
	if (!this->_isError)
	{
		this->_isError = true;
		this->_error = error;
	}
}

void				Puzzle::printDebug(std::string debug)
{
	if (this->_isError)
		return ;
	if (this->checkSum(D_OPT))
		std::cout << debug << std::endl;
}

void				Puzzle::debugPuzzle(std::string debug, t_matrix puzzle)
{
	if (this->_isError)
		return ;
	this->printDebug(debug);
	if (this->checkSum(D_OPT))
	{
		printPuzzle(puzzle);
		std::cout << std::endl;
	}
}

/*
** GRAPHICAL
*/

void				Puzzle::printHelp(void)
{
	int		x;
	int		y;

	x = this->_map.getWidth() / 3;
	y = this->_map.getHeight() / 3;
	mvwprintw(this->_map.getWin(), 0, x + 4, "==== HELP ====");
	if (y == 0)
		y = 1;
	mvwprintw(this->_map.getWin(), y, x, "Keys:");
	mvwprintw(this->_map.getWin(), y + 1, x + 4, "- Q to exit");
	mvwprintw(this->_map.getWin(), y + 2, x + 4, "- H to exit help or resume help");
	mvwprintw(this->_map.getWin(), y + 3, x + 4, "- P to pause or play");
	mvwprintw(this->_map.getWin(), y + 4, x + 4, "- ARROWS to move puzzle");
	mvwprintw(this->_map.getWin(), y + 5, x + 4, "- A and D to go back and forth the solution");
	mvwprintw(this->_map.getWin(), y + 6, x + 4, "- - and = to lower and add speed");
	mvwprintw(this->_map.getWin(), y + 7, x + 4, "- HOME key to get default values");
}

void				Puzzle::printSolution(int c_time, int c_size, int nb_moves, float total_time)
{
	int			bw;
	int			x;
	int			y;
	int			inter;
	int			size;
	int			center_x;
	int			center_y;

	if (this->_help)
		return ;
	inter = 1;
	size = this->_size;
	bw = numsize(size * size) + 2;
	center_x = (this->_map.getWidth() - size * bw - size * inter) / 2 + this->_x;
	center_y = (this->_map.getHeight() - size * 3 - size * inter) / 2 + this->_y;
	x = center_x;
	y = center_y + (size * 3) + (size * inter) + 1;
	if (nb_moves >= 0)
		mvwprintw(this->_map.getWin(), y, x, "Number of moves: %d", nb_moves);
	if (c_time >= 0)
		mvwprintw(this->_map.getWin(), y + 1, x, "Complexity in time: %d", c_time);
	if (c_size >= 0)
		mvwprintw(this->_map.getWin(), y + 2, x, "Complexity in size: %d", c_size);
	if (total_time >= 0.00)
		mvwprintw(this->_map.getWin(), y + 3, x, "Calculation time: %fs", total_time);
}

void				Puzzle::graphPuzzle(t_matrix puzzle)
{
	int			bw;
	int			x;
	int			y;
	int			inter;
	int			size;
	int			center_x;
	int			center_y;

	if (this->_help)
	{
		this->printHelp();
		return ;
	}
	inter = 1;
	size = this->_size;
	bw = numsize(size * size) + 2;
	center_x = (this->_map.getWidth() - size * bw - size * inter) / 2 + this->_x;
	center_y = (this->_map.getHeight() - size * 3 - size * inter) / 2 + this->_y;
	y = 0;
	if (this->_paused)
	{
		mvwprintw(this->_map.getWin(), 2, this->_map.getWidth() / 2 - (sizeof("Paused") / 2), "Paused");
		mvwprintw(this->_map.getWin(), 3, this->_map.getWidth() / 2 - (sizeof("Speed: ") / 2), "Speed: %d", -this->_speed);
	}
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			this->printBlock(center_x, center_y, y, x, puzzle[y][x], bw, inter);
			x++;
		}
		y++;
	}
}

void				Puzzle::printBlock(int cx, int cy, int y, int x, int num, int size, int inter)
{
	int		y2;
	int		x2;
	int		tmp_x;

	y = cy + y * 3 + y * (inter);
	tmp_x = cx + x * (size + 1) + x * (inter);
	x2 = tmp_x + size + 1;
	y2 = y + 3;
	if (!num)
		wattron(this->_map.getWin(), COLOR_PAIR(RED) | A_REVERSE);
	else
		wattron(this->_map.getWin(), COLOR_PAIR(WHITE) | A_REVERSE);
	while (y < y2)
	{
		x = tmp_x;
		while (x < x2)
		{
			if ((x >= 0 && x <= this->_map.getWidth()) && (y >= 0 && y <= this->_map.getHeight()))
			{
				mvwaddch(this->_map.getWin(), y, x, ' ');
				if ((x + x2) / 2 == x && (y + y2) / 2 == y)
					mvwprintw(this->_map.getWin(), y - 1, x - numsize(num), "%d", num);
			}
			x++;
		}
		y++;
	}
	if (!num)
		wattroff(this->_map.getWin(), COLOR_PAIR(RED) | A_REVERSE);
	else
		wattroff(this->_map.getWin(), COLOR_PAIR(WHITE) | A_REVERSE);
}

Map &				Puzzle::getMap(void)
{
	return (this->_map);
}

void				Puzzle::setMap(int h, int w)
{
	this->_map = Map(w, h);
}

void				Puzzle::setCurses(void)
{
	int		h;
	int		w;

	initscr();
	start_color();
	init_pair(42, COLOR_WHITE, COLOR_BLACK);
	noecho();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, h, w);
	this->setMap(h, w);
	wbkgd(this->_map.getWin(), COLOR_PAIR(42));
	keypad(this->_map.getWin(), TRUE);
	nodelay(this->_map.getWin(), TRUE);
}

bool				Puzzle::getFinished(void) const
{
	return (this->_finished);
}

Node				*getFirst(Node *path, int *index)
{
	while (path->get_prev_state())
	{
		path = path->get_prev_state();
		*index -= 1;
	}
	return (path);
}

void				Puzzle::parseKey(int keycode, Node **path, int *index)
{
	int			h;
	int			w;

	switch (keycode)
	{
		case 'q':
			this->_finished = true;
			break ;
		case KEY_RESIZE:
			wclear(this->getMap().getWin());
			wrefresh(this->getMap().getWin());
			delwin(this->getMap().getWin());
			resize_term(0, 0);
			getmaxyx(stdscr, h, w);
			this->setMap(h, w);
			wbkgd(this->_map.getWin(), COLOR_PAIR(42));
			keypad(this->getMap().getWin(), TRUE);
			nodelay(this->getMap().getWin(), TRUE);
			break ;
		case 'h':
			this->_help = this->_help == true ? false : true;
			if (this->_help)
				this->_paused = true;
			break ;
		case 'p':
			if (!this->_help)
				this->_paused = this->_paused == true ? false : true;
			break ;
		case KEY_HOME:
			this->_x = 0;
			this->_y = 0;
			this->_paused = true;
			this->_help = false;
			*path = getFirst(*path, index);
			break ;
		case KEY_LEFT:
			if (!this->_help)
				this->_x -= 4;
			break ;
		case KEY_RIGHT:
			if (!this->_help)
				this->_x += 4;
			break ;
		case KEY_UP:
			if (!this->_help)
				this->_y -= 2;
			break ;
		case KEY_DOWN:
			if (!this->_help)
				this->_y += 2;
			break ;
		case '=':
			if (!this->_help)
				this->_speed -= 10000;
			break ;
		case '-':
			if (!this->_help)
				this->_speed += 10000;
			break ;
		case 'a':
			if (!this->_help && *index > 0)
			{
				this->_paused = true;
				*path = (*path)->get_prev_state();
				*index -= 1;
			}
			break;
		case 'd':
			if (!this->_help && (*path)->get_next_state())
			{
				this->_paused = true;
				*path = (*path)->get_next_state();
				*index += 1;
			}
			break;
	}
	wrefresh(this->_map.getWin());
}

void				Puzzle::exitCurses(void)
{
	delwin(this->_map.getWin());
	endwin();
}

/*
** END GRAPHICAL
*/

t_matrixLine		Puzzle::getLineContent(std::string line, int size)
{
	unsigned int				i;
	int							j;
	t_matrixLine				lst(size);
	std::stringstream			ss;
	std::vector<std::string>	x;
	int							numSize;

	x = split(line, ' ');
	i = 0;
	j = 0;
	numSize = numsize(size * size);
	while (i < x.size() && j < size && !this->_isError)
	{
		if (!x[i].empty())
		{
			if ((int)x[i].size() > numSize)
			{
				this->setError("Number too high for this puzzle");
				break ;
			}
			ss << x[i];
			ss >> lst[j];
			ss.str("");
			ss.clear();
			j++;
		}
		i++;
	}
	return (lst);
}

static bool			strdigit(std::string line)
{
	int			i;
	const char	*s;

	i = 0;
	s = line.c_str();
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t'
			&& (s[i] < '0' || s[i] > '9'))
			return (false);
		i++;
	}
	return (true);
}

static void			strtrim(std::string & line)
{
	int			i;
	std::string	s;

	i = 0;
	while (line[i])
	{
		if (std::isspace(line[i]))
			s += " ";
		while (line[i] && std::isspace(line[i]))
			i++;
		if (line[i])
		{
			s += line[i];
			i++;
		}
	}
}

void				Puzzle::fillPuzzle(std::list<std::string> file)
{
	std::size_t							index;
	int									size;
	int									total_line;
	std::string							line;
	std::list<std::string>::iterator	it = file.begin();
	std::stringstream					ss;

	if (this->isError())
		return ;
	size = 0;
	total_line = 0;
	while (it != file.end() && !this->isError())
	{
		line = *it;
		index = line.find("#");
		line = line.substr(0, index);
		strtrim(line);
		if (!line.empty())
		{
			++total_line;
			if (!strdigit(line))
				this->setError("File malformated (Should only be numbers)");
			if (!size)
			{
				ss << line;
				ss >> size;
				this->setSize(size);
				ss.str("");
				ss.clear();
			}
			else
				this->_filePuzzle.push_back(this->getLineContent(line, size));
		}
		it++;
	}
	if (!size)
		this->setError("No size specified");
	if (total_line > size + 1)
		this->setError("Too much line specified");
}

void				Puzzle::checkIntegrity(t_matrix puzzle)
{
	t_matrix::iterator	it = puzzle.begin();
	unsigned long		i;

	if (this->isError())
		return ;
	std::vector<int>	check(this->getSize() * this->getSize(), 0);
	while (it != puzzle.end())
	{
		t_matrixLine::iterator	lineIt = (*it).begin();

		while (lineIt != (*it).end())
		{
			if (check[*lineIt])
				this->setError("File malformated");
			check[*lineIt] = 1;
			lineIt++;
		}
		it++;
	}
	i = 0;
	while (i < check.size())
	{
		if (!check[i])
		{
			this->setError("File malformated");
			break ;
		}
		i++;
	}
}

bool				Puzzle::checkSolvable(t_matrix puzzle)
{
	int					i;
	int					j;
	int					inversions;
	t_matrixLine		line;
	int					size;

	if (this->isError())
		return (false);
	i = 0;
	inversions = 0;
	size = puzzle.size() * puzzle.size();
	line = flatten(puzzle);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (line[i] && line[j] && line[i] > line[j])
				inversions++;
			j++;
		}
		i++;
	}
	if (inversions % 2 == 1)
	{
		this->setError("Unsolvable");
		return (false);
	}
	return (true);
}

static int			myrandom(int i)
{
	return (std::rand() % i);
}

static void			shuffleMatrix(t_matrix & matrix)
{
	std::random_shuffle(matrix.begin(), matrix.end(), myrandom);
}

static t_matrix		generateRandomMatrix(int size)
{
	t_matrixLine			rand(size * size);
	t_matrix				ret(size, t_matrixLine(size));
	int						i;

	for (int j = 0 ; j < size * size ; j++)
		rand[j] = j;
	std::random_shuffle(rand.begin(), rand.end(), myrandom);
	i = 0;
	while (i < size * size)
	{
		ret[i / size][i % size] = rand[i];
		i++;
	}
	return (ret);
}

void				Puzzle::setPuzzle(char *filename)
{
	std::ifstream			myfile;
	std::string				line;
	std::list<std::string>	lst;
	std::string				file;

	if (this->checkSum(S_OPT))
	{
		//Read from stdin
		while (std::getline(std::cin, line))
			lst.push_back(line);
	}
	else if (filename && this->checkSum(F_OPT))
	{
		//Read from file
		file = std::string(filename);
		myfile.open(filename);
		if (!myfile || !myfile.is_open())
		{
			this->setError("Could not open file " + file);
			return ;
		}
		while (std::getline(myfile, line))
			lst.push_back(line);
		myfile.close();
	}
	else if (!this->checkSum(O_OPT))
		this->setError("Please specify a file or read from input");

	//Auto generate puzzle
	if (!this->_isError && this->checkSum(O_OPT))
	{
		this->_filePuzzle = generateRandomMatrix(this->_size);
		shuffleMatrix(this->_filePuzzle);
		if (!this->checkSolvable(this->_filePuzzle))
		{
			iter_swap(this->_filePuzzle.begin(), this->_filePuzzle.begin() + 1);
			this->_isError = false;
			this->_error = std::string("");
		}
		this->checkSolvable(this->_filePuzzle);
	}
	else if (!this->_isError)
	{
		//Fill puzzle by lines
		this->fillPuzzle(lst);
		this->checkIntegrity(this->_filePuzzle);
		this->checkSolvable(this->_filePuzzle);
	}
	if (!this->_isError)
	{
		this->_puzzle = this->_filePuzzle;
		this->_endPuzzle = generateSnail(this->_size);
	}
	this->debugPuzzle("PUZZLE", this->_filePuzzle);
	//this->getDict(this->getEndPuzzle());
	//this->_puzzle = this->getDicted(this->_filePuzzle);
}
