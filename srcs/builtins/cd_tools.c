/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 23:03:42 by brice             #+#    #+#             */
/*   Updated: 2021/07/20 23:03:46 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_cd(void *str1, void *str2, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, 2);
	if (str2 != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str2, 2);
	}
	if (err != -10)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(err), 2);
	}
}

int	pwd_error(char	**current_pwd, char *path)
{
	if (!*current_pwd)
	{
		print_error_cd("cd", path, errno);
		g_signals.exit_status = 1;
		free(*current_pwd);
		return (ERROR);
	}
	return (1);
}

int	else_argument(t_minishell *minishell, t_node *curr_pwd, char **path)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, PATH_MAX);
	if (pwd_error(&current_pwd, *path) == ERROR)
		return (ERROR);
	if (curr_pwd)
		add_var(minishell, ft_strjoin("PWD=", current_pwd), 1);
	return (0);
}
