
#include "minishell.h"
#include <signal.h>
#include "readline/readline.h"

void	sigint_save_status(int status)
{
	if (!signals.sig_int)
	{
		signals.exit_status = WEXITSTATUS(status);
	}
	else
	{
		signals.sig_int = 0;
	}
	signals.pid = 0;
}

void	sigint_handler(int sig)
{
	char	*buf;

	buf = NULL;
	if (!signals.pid)
	{
		buf = ft_strdup(rl_line_buffer);
		if (!buf)
			return ;
		ft_putstr_fd(PROMPT, 1);
		ft_putstr_fd(buf, 1);
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free(buf);
		signals.exit_status = 1;
	}
	else
	{
		printf("hey\n");
		write(1, "\n", 1);
		// rl_on_new_line();
		// // rl_replace_line("", 0);
		// rl_redisplay();
		signals.exit_status = 130;
		signals.sig_int = 1;
		signals.pid = 0;
	}
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT && signals.pid)
	{
		printf("Quite:\n");
	}
}