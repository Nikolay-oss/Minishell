/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:52:19 by brice             #+#    #+#             */
/*   Updated: 2021/07/20 23:03:09 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_check_home(t_minishell *minishell, t_node *curr_pwd, char *str)
{
	char	*current_pwd;
	char	*err;

	current_pwd = getcwd(NULL, PATH_MAX);
	if (current_pwd && curr_pwd)
	{
		err = ft_strjoin(str, current_pwd);
		if (!err)
		{
			ft_malloc_error(minishell);
			return (ERROR);
		}
		add_var(minishell, err, 1);
	}
	free(current_pwd);
	return (0);
}

int	home_set(t_minishell *minishell, t_node	*curr_pwd, char *path)
{
	t_node	*old_pwd;
	t_node	*home_pwd;

	old_pwd = getvar_node(minishell->env, "OLDPWD");
	home_pwd = getvar_node(minishell->env, "HOME");
	if (home_pwd)
	{
		if (err_check_home(minishell, old_pwd, "OLDPWD=") == ERROR)
			 return (ERROR);
		if (chdir(&((home_pwd->content)[5])) == ERROR)
		{
			print_error_cd("cd", path, errno);
			g_signals.exit_status = 1;
		}
		if (err_check_home(minishell, curr_pwd, "PWD=") == ERROR)
			return (ERROR);
	}
	else
	{
		print_error_cd("cd", "HOME not set\n", -10);
		g_signals.exit_status = 1;
	}
	return (0);
}

void	update_path(int arg, t_minishell *minishell, char **path)
{
	t_node	*curr_pwd;
	t_node	*old_pwd;
	char	*current_pwd;

	g_signals.exit_status = 0;
	curr_pwd = getvar_node(minishell->env, "PWD");
	old_pwd = getvar_node(minishell->env, "OLDPWD");
	if (arg == 0)
		home_set(minishell, curr_pwd, *path);
	else if (arg == 1)
	{
		current_pwd = getcwd(NULL, PATH_MAX);
		if (pwd_error(&current_pwd, *path) == ERROR)
			return ;
		if (old_pwd)
			add_var(minishell, ft_strjoin("OLDPWD=", current_pwd), 1);
		free(current_pwd);
		if (chdir(*path) == ERROR)
		{
			print_error_cd("cd", *path, errno);
			g_signals.exit_status = 1;
		}
		else
			else_argument(minishell, curr_pwd, path);
	}
}

void	ft_cd(t_minishell *minishell, char *path)
{
	if (!path || !ft_strcmp(path, "~"))
		update_path(0, minishell, &path);
	else
		update_path(1, minishell, &path);
}
