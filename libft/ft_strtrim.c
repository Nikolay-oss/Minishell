/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:57:02 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:44:20 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isforbiden(char const *set, char const c)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	init_idx(char const *s1)
{
	size_t	idx;

	idx = ft_strlen(s1);
	if (!idx)
		return (1);
	else
		return (idx - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	if (!s1)
		return ((char *)s1);
	i = 0;
	j = init_idx(s1);
	while (i <= j)
	{
		if (isforbiden(set, *(s1 + i)))
			i++;
		else if (isforbiden(set, *(s1 + j)))
			j--;
		else
			break ;
	}
	str = ft_calloc(j - i + 2, sizeof(char));
	if (!str)
		return (str);
	k = 0;
	while (i <= j)
		*(str + k++) = *(s1 + i++);
	return (str);
}
