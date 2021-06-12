/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:24:15 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:26:53 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
	size_t n)
{
	unsigned char	*str_dst;
	unsigned char	*str_src;
	size_t			i;

	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(str_dst + i) = *(str_src + i);
		if (*(str_src + i) == (unsigned char)c)
			return (str_dst + i + 1);
		i++;
	}
	return (NULL);
}
