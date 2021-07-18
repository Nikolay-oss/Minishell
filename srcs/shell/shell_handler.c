#include <signal.h>
//<<<<<<< HEAD
////#include <bits/signum-generic.h>
//=======
//// #include <bits/signum-generic.h>
//>>>>>>> 758c28cf67f6d344a59882ad521dddd1cf3ea55c
#include "minishell.h"
#include <signal.h>

void	shell_handler(t_minishell *minishell)
{
	heredocs_handler(minishell);
	minishell->cnt_prcs = -1;

//	signal(SIGQUIT, &sigquit_handler);
//	if (errno == (int) SIG_ERR)
//		print_error("signal", errno);

	if (minishell->pipes_count > 0)
	{
		signal(SIGQUIT, &sigquit_handler);
		if (errno == (int) SIG_ERR)
			print_error("signal", errno);
		ft_pipes(minishell, minishell->commands, 0);
		signal(SIGQUIT, SIG_IGN);
		if (errno == (int) SIG_ERR)
			print_error("signal", errno);
	}
	else
	{
		signal(SIGQUIT, &sigquit_handler);
		if (errno == (int) SIG_ERR)
			print_error("signal", errno);
		redir_handler(minishell, minishell->commands, 0, 1);
		signal(SIGQUIT, SIG_IGN);
		if (errno == (int) SIG_ERR)
			print_error("signal", errno);
	}
	if (minishell->heredocs)
		destroy_heredocs(minishell);
}
