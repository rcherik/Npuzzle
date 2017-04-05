/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseArgs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 18:42:19 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/12 18:47:06 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include "Puzzle.class.hpp"

static char		*getCmdOption(char **begin, char **end, const std::string & option)
{
	unsigned long				i;
	char						**itr;
	std::vector<std::string>	x;

	x = split(option, ' ');
	i = 0;
	while (i < x.size())
	{
		itr = std::find(begin, end, x[i]);
		if (itr && itr != end && (itr + 1) && (itr + 1) != end)
			return (*(itr + 1));
		i++;
	}
	return (NULL);
}

static bool		cmdOptionExists(char** begin, char** end, const std::string & option)
{
	unsigned long				i;
	std::vector<std::string>	x;

	x = split(option, ' ');
	i = 0;
	while (i < x.size())
	{
		if (std::find(begin, end, x[i]) != end)
			return (true);
		i++;
	}
	return (false);
}

static int		usage(void)
{
	std::cerr << "n_puzzle: Usage: " << "./n_puzzle [-s --stdout | -f --file [FILE] | -o --auto-generate [SIZE]]";
	std::cerr << " [-a --algorithm manhattan(1)/toorc(2)/hamming(3)/gaschnig(4)] [-g --graphical]" << std::endl;
	return (1);
}

static int		isArg(char *argv)
{
	std::string					s = argv;
	std::vector<std::string>	x1 = split("-s --stdout -g --graphical -d --debug", ' ');
	std::vector<std::string>	x2 = split("-f --file -o --auto-generate -a --algorithm", ' ');
	unsigned int				i;

	i = 0;
	while (i < x1.size())
	{
		if (s == x1[i])
			return (1);
		i++;
	}
	i = 0;
	while (i < x2.size())
	{
		if (s == x2[i])
			return (2);
		i++;
	}
	error("invalid argument '" + s + "'");
	return (-1);
}

static int		readArgs(int argc, char **argv)
{
	int		i;
	int		adv;
	
	i = 1;
	while (i < argc)
	{
		if ((adv = isArg(argv[i])) == -1)
			return (1);
		else
			i += adv;
	}
	return (0);
}

int				parseArgs(int argc, char **argv, Puzzle & puzzle)
{
	char				*filename;
	char				*algo;
	int					sum;
	int					size;
	char				*size_str;
	std::string			size_string;
	std::stringstream	ss;

	filename = NULL;
	algo = NULL;
	sum = 0;
	if (argc < 2)
		return (usage());
	if (cmdOptionExists(argv, argv + argc, "-h --help"))
		return (usage());
	if (readArgs(argc, argv))
		return (1);
	if (cmdOptionExists(argv, argv + argc, "-o --auto-generate"))
	{
		sum += O_OPT;
		if ((size_str = getCmdOption(argv, argv + argc, "-o --auto-generate")))
		{
			size_string = std::string(size_str);
			ss << size_string;
			if (!size_string.empty() && size_string.find_first_not_of("0123456789") == std::string::npos)
			{
				ss >> size;
				puzzle.setSize(size);
			}
			else
				return (error("Not a number : " + size_string));
		}
		else
			return (error("No size given after -o or --auto-generate option"));
	}
	if (cmdOptionExists(argv, argv + argc, "-f --file"))
	{
		if ((sum & O_OPT))
			return (error("You can't generate a puzzle and read from a file"));
		if (!(filename = getCmdOption(argv, argv + argc, "-f --file")))
			return (error("No file given after -f or --file option"));
		sum += F_OPT;
	}
	if (cmdOptionExists(argv, argv + argc, "-s --stdin"))
	{
		if ((sum & O_OPT))
			return (error("You can't generate a puzzle and read from stdin"));
		if (filename)
			return (error("You can't read from stdin and a file"));
		sum += S_OPT;
	}
	if (cmdOptionExists(argv, argv + argc, "-g --graphical"))
		sum += G_OPT;
	if (cmdOptionExists(argv, argv + argc, "-d --debug"))
		sum += D_OPT;
	if (cmdOptionExists(argv, argv + argc, "-a --algorithm"))
	{
		if (!(algo = getCmdOption(argv, argv + argc, "-a --algorithm")))
			return (error("No algorithm given after -a or --algorithm option"));
		sum += A_OPT;
	}
	puzzle.setSum(sum);
	puzzle.setAlgo(algo);
	puzzle.setPuzzle(filename);
	if (puzzle.isError())
		return (error(puzzle.getError()));
	return (0);
}
