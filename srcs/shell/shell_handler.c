/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 00:39:49 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/20 00:39:50 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	shell_handler(t_minishell *minishell)
{
	heredocs_handler(minishell);
	minishell->cnt_prcs = -1;
	if (minishell->pipes_count > 0)
	{
		signal(SIGQUIT, &sigquit_handler);
		ft_pipes(minishell, minishell->commands, 0);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGQUIT, &sigquit_handler);
		redir_handler(minishell, minishell->commands, 0, 1);
		signal(SIGQUIT, SIG_IGN);
	}
	if (minishell->heredocs)
		destroy_heredocs(minishell);
	g_signals.pid = 0;
}
