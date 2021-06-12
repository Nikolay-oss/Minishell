#include "ft_parser.h"
#include "libft.h"
#include "minishell.h"
#include "data_types.h"
#include <stdlib.h>

void	destroy_command_buf(char **command)
{
	t_uint	i;

	i = 0;
	while (*(command + i))
		free(*(command + i++));
	free(command);
}

void	ft_parser(char *buf)
{
	char	**command;

	command = ft_split(buf, ' ');
	if (*command)
	{
		select_command(command);
		destroy_command_buf(command);
	}
}
