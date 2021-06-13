#include "ft_parser.h"
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

void	ft_parser(t_minishell *minishell, char *buf)
{
	char	**command;

	command = ft_split(buf, ' ');
	if (*command)
	{
		select_command(minishell, command);
		destroy_command_buf(command);
	}
}
