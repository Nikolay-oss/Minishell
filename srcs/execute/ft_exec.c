#include "minishell.h"
#include <sys/wait.h>

void	make_path_to_bin(t_minishell *minishell, char *path, char *cmd_bin,
	char **cmd_bin_out)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	*cmd_bin_out = ft_strjoin(tmp, cmd_bin);
	if (!*cmd_bin_out)
	{
		ft_malloc_error(minishell);
		return ;
	}
	free(tmp);
}

void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc)
{
	char	*path_to_bin;
	pid_t	pid;
	int		status;
	char	**envp;

	path_to_bin = NULL;
	save_path_to_bin(minishell, *cmd, &path_to_bin);
	if (!path_to_bin)
		return ;
	envp = ft_lst_to_strs(minishell->env);
	if (create_proc)
	{
		pid = fork();
		if (pid == 0)
			execve(path_to_bin, cmd, envp);
		else
			waitpid(pid, &status, 0);
		minishell->exit_status = WEXITSTATUS(status);
	}
	else
		execve(path_to_bin, cmd, envp);
	free(path_to_bin);
}