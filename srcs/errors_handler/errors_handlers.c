/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:51:15 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/15 00:37:35 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_bool	search_arg_ehandler(t_minishell *minishell, int isquotes, char **arg,
	char *buf)
{
	int	status;

	status = add_arg(minishell, arg, buf);
	if (status == 2)
		return (1);
	else if (!status)
		return (0);
	if (!add_to_f_quotes(minishell, isquotes))
		return (0);
	return (1);
}

t_bool	add_pipe_ehandler(t_minishell *minishell, char *buf)
{
	if (!add_command_to_allcommands(minishell, buf, 1))
		return (0);
	if (!add_to_f_quotes(minishell, 0))
		return (0);
	return (1);
}

void	dup_ehandler()
{
	signals.exit_status = errno;
	print_error("dup", errno);
}
