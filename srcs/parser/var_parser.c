/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:32 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:50:33 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	var_parser(char *str)
{
	t_uint	i;
	t_bool	num_flag;

	if (*str == '=')
		return (0);
	num_flag = 0;
	i = 0;
	while (*(str + i) && *(str + i) != '=')
	{
		if (ft_isalpha(*(str + i)) || *(str + i) == '_')
			num_flag = 1;
		else if (!num_flag && ft_isdigit(*(str + i)))
			return (0);
		else if (!ft_isalnum(*(str + i)) && *(str + i) != '_')
			return (0);
		i++;
	}
	return (1);
}
