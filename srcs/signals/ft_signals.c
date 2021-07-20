/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 22:09:07 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/20 23:10:02 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include "readline/readline.h"

void	save_status(int status)
{
	if (WIFEXITED(status))
		g_signals.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signals.exit_status = 128 + WTERMSIG(status);
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (!g_signals.pid)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signals.exit_status = 1;
	}
	else
	{
		write(1, "\n", 1);
	}
}

void	sigquit_handler(int sig)
{
	char	*nbr;

	nbr = ft_itoa(sig);
	if (g_signals.pid)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
	}
	free(nbr);
}
