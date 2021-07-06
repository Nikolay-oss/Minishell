#include "minishell.h"

void	print_error(char *str, int errorcode)
{
	char	*error;

	error = strerror(errorcode);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

void	command_not_found(char *str, int errorcode)
{
	if (errorcode == 127)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
	}
}

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

void	isdir_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": Is a directory", 2);;
}
