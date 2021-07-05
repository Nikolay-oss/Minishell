#include "minishell.h"
#include <sys/wait.h>
#include <dirent.h>

static void	search_binfile()
{
	DIR	*dir;

	dir = opendir("/bin");
	if (dir)
		printf("dir exists\n");
	else
		printf("dir not exists\n");
	ft_putendl_fd(strerror(errno), 2);
	if (dir)
		closedir(dir);
}

int	ft_exec(t_list *env, char **cmd, t_bool create_proc)
{

	search_binfile();
	// int	exit_code;

	// if (fork() == 0)
	// {
	// 	exit_code = execve("/bin/ls", cmd, NULL);
	// }
	// else
	// 	wait(&exit_code);
	// return (WEXITSTATUS(exit_code));
}