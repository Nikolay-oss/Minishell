/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:39:55 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:36:37 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (str + i);
		i++;
	}
	if (*(str + i) == c)
		return (str + i);
	return (NULL);
}
