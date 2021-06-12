/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:03:17 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:37:51 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	*current;

	str = (char *)s;
	i = 0;
	current = NULL;
	while (*(str + i))
	{
		if (*(str + i) == c)
			current = str + i;
		i++;
	}
	if (*(str + i) == c)
		return (str + i);
	return (current);
}
