/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:50:20 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 20:50:21 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

t_bool	isredir(const char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

t_bool	ispipe(const char c)
{
	if (c == '|')
		return (1);
	return (0);
}
