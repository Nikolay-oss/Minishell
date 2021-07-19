/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_dual_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:47:49 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/20 00:00:11 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

t_bool	launch_dual_redir(t_minishell *minishell, int n_proc)
{
	int	status;

	status = 0;
	if (*(minishell->heredocs + n_proc))
	{
		status = ft_redir(*(minishell->heredocs + n_proc), O_RDONLY, 0, 0);
		if (status > 0)
			return (0);
	}
	return (1);
}
