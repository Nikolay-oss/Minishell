/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:02:34 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 22:02:35 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_del_substr(const char *s, const char *set)
{
	char	*str;
	size_t	set_size;
	size_t	str_size;
	size_t	i;

	i = 0;
	set_size = ft_strlen(set);
	str_size = 0;
	while (*(s + i))
	{
		if (!ft_memchr(set, *(s + i), set_size))
			str_size++;
		i++;
	}
	str = (char *)ft_calloc(str_size + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (*(s + --i) && str_size)
	{
		if (!ft_memchr(set, *(s + i), set_size))
			*(str + --str_size) = *(s + i);
	}
	return (str);
}
