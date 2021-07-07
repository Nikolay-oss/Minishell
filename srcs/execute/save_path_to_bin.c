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
		minishell->exit_status = 127;
		print_error(cmd_bin, errno);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		minishell->exit_status = 126;
		print_error(cmd_bin, 21);
	}
	else
	{
		minishell->exit_status = 0;
		*cmd_bin_out = ft_strdup(cmd_bin);
	}
}

static void	cmp_filenames(t_minishell *minishell, char *cmd_bin, DIR *dir)
{
	struct dirent	*ent;

	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(cmd_bin, ent->d_name))
		{
			minishell->exit_status = 0;
			break ;
		}
		else
			minishell->exit_status = 127;
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
			cmp_filenames(minishell, cmd_bin, dir);
			closedir(dir);
		}
		else
			minishell->exit_status = 127;
		if (minishell->exit_status == 0)
			break ;
		i++;
	}
	if (minishell->exit_status == 0)
		make_path_to_bin(*(paths + i), cmd_bin, cmd_bin_out);
	command_not_found(cmd_bin, minishell->exit_status);
}

static void	search_bin_file(t_minishell *minishell, char *cmd_bin,
	char **cmd_bin_out)
{
	char	*path_var;
	char	**paths;

	path_var = getvar_value(minishell->env, "PATH");
	if (path_var)
	{
		paths = ft_split(path_var, ':');
		check_filenames(minishell, cmd_bin, cmd_bin_out, paths);
		destroy_command_buf(paths);
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
	*cmd_bin_out = NULL;
	if (p_slesh)
		check_file(minishell, cmd_bin, cmd_bin_out);
	else
		search_bin_file(minishell, cmd_bin, cmd_bin_out);
}
