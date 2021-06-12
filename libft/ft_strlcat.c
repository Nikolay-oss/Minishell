/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:44:32 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:37:28 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	dst_size;

	size = 0;
	dst_size = ft_strlen(dst);
	i = 0;
	while (*(dst + i))
		i++;
	if (dstsize > dst_size)
		size = dstsize - i - 1;
	else
		return (ft_strlen(src) + dstsize);
	j = 0;
	while (j < size && *(src + j))
	{
		*(dst + i) = *(src + j);
		i++;
		j++;
	}
	*(dst + i) = '\0';
	return (ft_strlen(src) + dst_size);
}
