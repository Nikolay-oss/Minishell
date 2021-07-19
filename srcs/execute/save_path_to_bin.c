/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path_to_bin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:51:30 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/19 23:38:22 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/stat.h>

static void	check_file(t_minishell *minishell, char *cmd_bin,
	char **cmd_bin_out)
{
	struct stat	buf;
	int			isexists;

	isexists = stat((const char *)cmd_bin, &buf);
	if (isexists < 0)
	{
		g_signals.exit_status = 127;
		print_error(cmd_bin, errno);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		g_signals.exit_status = 126;
		print_error(cmd_bin, 21);
	}
	else
	{
		g_signals.exit_status = 0;
		*cmd_bin_out = ft_strdup(cmd_bin);
		if (!*cmd_bin_out)
			ft_malloc_error(minishell);
	}
}

static void	cmp_filenames(char *cmd_bin, DIR *dir)
{
	struct dirent	*ent;

	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(cmd_bin, ent->d_name))
		{
			g_signals.exit_status = 0;
			break ;
		}
		else
			g_signals.exit_status = 127;
		ent = readdir(dir);
	}
}

static void	check_filenames(t_minishell *minishell, char *cmd_bin,
	char **cmd_bin_out, char **paths)
{
	DIR		*dir;
	t_uint	i;

	i = 0;
	while (*(paths + i))
	{
		dir = opendir(*(paths + i));
		if (dir)
		{
			cmp_filenames(cmd_bin, dir);
			closedir(dir);
		}
		else
			g_signals.exit_status = 127;
		if (g_signals.exit_status == 0)
			break ;
		i++;
	}
	if (g_signals.exit_status == 0)
		make_path_to_bin(minishell, *(paths + i), cmd_bin, cmd_bin_out);
	command_not_found(cmd_bin, g_signals.exit_status);
}

static void	search_bin_file(t_minishell *minishell, char *cmd_bin,
	char **cmd_bin_out)
{
	char	*path_var;
	char	**paths;

	path_var = getvar_value(minishell, minishell->env, "PATH");
	if (minishell->ismem_error)
		return ;
	if (path_var)
	{
		paths = ft_split(path_var, ':');
		if (!paths)
		{
			ft_malloc_error(minishell);
			free(path_var);
			return ;
		}
		check_filenames(minishell, cmd_bin, cmd_bin_out, paths);
		destroy_arr2d(paths);
		free(path_var);
	}
	else
		check_file(minishell, cmd_bin, cmd_bin_out);
}

void	save_path_to_bin(t_minishell *minishell, char *cmd_bin,
	char **cmd_bin_out)
{
	char	*p_slesh;
	char	*paths;

	p_slesh = ft_strchr(cmd_bin, '/');
	if (p_slesh)
		check_file(minishell, cmd_bin, cmd_bin_out);
	else
		search_bin_file(minishell, cmd_bin, cmd_bin_out);
}
