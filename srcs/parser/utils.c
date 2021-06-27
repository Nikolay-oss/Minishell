/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:06 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/22 21:58:54 by dkenchur         ###   ########.fr       */
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

void	add_command_to_list(t_minishell *minishell, char *buf, t_uint idx)
{
	char	*str_cmd;
	char	chr_endcmd;

	chr_endcmd = *(buf + idx);
	*(buf + idx) = 0;
	str_cmd = ft_strdup(buf);
	if (!str_cmd)
		return ; // error
	*(buf + idx) = chr_endcmd;
	ft_push_back(minishell->commands, str_cmd);
}

void	change_flag(t_bool *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}

char	*check_memory(char **str)
{
	if (!*str)
		; // error
	return (*str);
}
