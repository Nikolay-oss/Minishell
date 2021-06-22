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

void	destroy_command_buf(char **command)
{
	t_uint	i;

	i = 0;
	while (*(command + i))
		free(*(command + i++));
	free(command);
}

void	copy_command(char *buf, char **str_cmd, t_uint idx)
{
	char	cmdend;

	cmdend = *(buf + idx);
	*(buf + idx) = 0;
	*str_cmd = ft_strdup(buf);
	*(buf + idx) = cmdend;
}

void	change_flag(t_bool *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}
