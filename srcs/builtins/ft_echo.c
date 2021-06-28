#include "minishell.h"

void	ft_echo(char **command)
{
	t_uint	args_count;
	t_bool	is_n_opt;
	t_uint	i;

	args_count = ft_count_args(command);
	is_n_opt = 0;
	i = 0;
	while (i < args_count && !ft_strcmp(*(command + i), "-n"))
	{
		is_n_opt = 1;
		i++;
	}
	while (i < args_count)
	{
		ft_putstr_fd(*(command + i), 1);
		if (i + 1 < args_count)
			write(1, " ", 1);
		i++;
	}
	if (!is_n_opt)
		write(1, "\n", 1);
}
