/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index_symbol.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:02:44 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 22:02:45 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_index_symbol(char *str, char find)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == find)
			return i;
		i++;
	}
	return (-1);
}