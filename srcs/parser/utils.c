/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:06 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/19 23:59:24 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_uint	skip_spaces(char *str)
{
	t_uint	i;

	i = 0;
	while (*(str + i) == ' ')
		i++;
	return (i);
}

t_bool	add_command_to_allcommands(t_minishell *minishell, char *buf,
	t_uint idx)
{
	char	*str_cmd;
	char	chr_endcmd;

	chr_endcmd = *(buf + idx);
	*(buf + idx) = 0;
	str_cmd = ft_strdup(buf);
	*(buf + idx) = chr_endcmd;
	if (!str_cmd)
		return (0);
	ft_push_back(minishell->all_commands, str_cmd);
	return (1);
}

void	change_flag(t_bool *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}

t_bool	check_memory(t_minishell *minishell, void *str)
{
	if (!str)
	{
		ft_malloc_error(minishell);
		return (0);
	}
	return (1);
}

void	init_range(t_uint *start, t_uint *end, t_uint s_val, t_uint e_val)
{
	*start = s_val;
	*end = e_val;
}
