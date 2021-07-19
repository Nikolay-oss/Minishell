/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:13 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/19 22:19:45 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_parser.h"

#include "readline/readline.h"
#include "readline/history.h"

t_signal	signals;

void	rl_replace_line();

static void	ft_loop(t_minishell *minishell)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		minishell->ismem_error = 0;
		buf = readline(PROMPT);
		if (!buf)
		{
			printf("\x1B[1F\e[%luC exit\n", ft_strlen("prompt>"));
			break ;
		}
		add_history(buf);
		ft_parser(minishell, buf);
		free(buf);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;

	(void)ac;
	(void)av;
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	if (!init_shell(minishell, envp))
		return (signals.exit_status);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
//	signal(SIGQUIT, &sigquit_handler);
	ft_loop(minishell);
	destroy_shell(minishell);
	// write(1, "exit\n", 5);
	return (signals.exit_status);
}


/*
"\4" - ^D
*/
/*
  export LDFLAGS="-L/Users/dkenchur/.brew/opt/readline/lib"
  export CPPFLAGS="-I/Users/dkenchur/.brew/opt/readline/include"
*/

// free(buf);
// tcgetattr(STDIN_FILENO, &term);
// term.c_lflag &= ~(ISIG);
// tcsetattr(STDIN_FILENO, TCSANOW, &term);

// environment variables
// int i = 0;
// while (*(envp + i))
// 	printf("%s\n", *(envp + i++));
