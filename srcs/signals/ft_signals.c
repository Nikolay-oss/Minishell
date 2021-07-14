
#include "minishell.h"
#include <signal.h>
#include "readline/readline.h"

void	ft_signals(int sig)
{

}

void	sigint_handler(int sig)
{
	char	*buf;

	buf = NULL;
	if (sig == SIGINT)
	{
		buf = ft_strdup(rl_line_buffer);
		if (!buf)
			return ;
		ft_putstr_fd(PROMPT, 2);
		ft_putstr_fd(buf, 2);
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free(buf);
		signals.exit_status = 1;
	}
}