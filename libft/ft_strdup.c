/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:19:12 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:36:42 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;
	size_t	i;

	size = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (str);
	i = 0;
	while (i < size)
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
