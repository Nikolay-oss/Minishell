#include "minishell.h"
#include <signal.h>
#include "readline/readline.h"

void	save_status(int status)
{
	if (WIFEXITED(status))
		signals.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		signals.exit_status = 128 + WTERMSIG(status);
}

void	sigint_handler(int sig)
{
	if (!signals.pid)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signals.exit_status = 1;
	}
	else
	{
		write(1, "\n", 1);
	}
}

void	sigquit_handler(int sig)
{
	char *nbr;

	nbr = ft_itoa(sig);
	if (signals.pid)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putstr_fd(nbr, 2);
		ft_putstr_fd("\n", 2);
	}
}
