/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:45:25 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:37:46 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len && *(haystack + i))
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) && len > i + j)
		{
			if (!*(needle + j + 1))
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
