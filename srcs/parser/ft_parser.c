#include "ft_parser.h"
#include "libft.h"
#include "minishell.h"

void	ft_parser(const char *buf)
{
	const char	**command;

	command = (const char **)ft_split(buf, ' ');
	if (*command)
		select_command(command);
}
