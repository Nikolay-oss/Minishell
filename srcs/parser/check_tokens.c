#include "ft_parser.h"

t_bool	isredir(const char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

t_bool	ispipe(const char c)
{
	if (c == '|')
		return (1);
	return (0);
}
