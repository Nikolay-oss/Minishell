/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:13 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/22 19:44:46 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
// #include <termios.h>

#include "ft_parser.h"

#include "readline/readline.h"
#include "readline/history.h"
/*
	global struct signals
*/

t_signal	signals;

void	rl_replace_line();

void	ft_handler(int sig)
{
	signals.sig_int = 1;
	(void)sig; // temprorary
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char			*buf;
	t_minishell		*minishell;
	// struct termios	term;

	(void)ac;
	(void)av;
	buf = NULL;
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (1);
	init_env(&minishell->env, envp); // в инит лучше передавать указаьтель на минишелл
	minishell->exit_status = (long long int)NULL; // 1
	minishell->home_path = (char *)NULL; // 2
	signals.sig_int = 0; // 3
	signals.sig_quit = 0; // 4
	minishell->home_path = getvar_value(minishell->env, "HOME");
	while (1)
	{
		signal(SIGINT, &ft_handler);
		buf = readline("\033[0;32mprompt> \033[0m");
		if (!buf)
			break ;
		// printf("%s\n", buf);
//		if (buf && !strcmp(buf, "exit"))
//			break ;
		add_history(buf);
		ft_parser(minishell, buf);
		free(buf);
	}
	// free(buf);
	ft_lst_clear(minishell->env, &free);
	free(minishell->home_path);
	free(minishell);
	write(1, "exit\n", 5);
	return (0);
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
