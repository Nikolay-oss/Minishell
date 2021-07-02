#include "ft_parser.h"


void	ft_exec(t_list *env, char **arv)
{
	int		result;
	int		status;
	int		i;
	char	**path_arr;
	char	*str_concat;
	char	*str_free;
	t_node	*node;
	pid_t	pid;

	result = -1;
//	pid = fork();
//	if (pid == 0)
//	{
		node = getvar_node(env, "PATH");
		i = ft_get_index_symbol(node->content, '=');
		path_arr = ft_split(&(node->content)[++i], ':');
		i = 0;
		while (path_arr[i] && result < 0)
		{
			str_concat = ft_strjoin(path_arr[i++], "/");
			str_free = str_concat;
			str_concat = ft_strjoin(str_concat, arv[0]);
			result = execve(str_concat, arv, NULL);
//			printf("|%d|\n", result);
//			if(result != -1)
//				break;
			free(str_concat);
			free(str_free);
//			printf("result $?:%d\n", result);
		}
//	exit(0);
		if (result == -1)
			printf("%s: command not found\n", *arv);
//		printf("result $?234234234:%d\n", 123);
//		printf("result $?:%d\n", result);
		destroy_command_buf(path_arr);
		exit(0);
//	}
//	else
//	{
//		wait(&status);
//	}
//	wait(&status);
}