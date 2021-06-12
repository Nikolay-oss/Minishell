/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:01:45 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:27:17 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str_dst;
	unsigned char	*str_src;

	if (dst == src)
		return (dst);
	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(str_dst + i) = *(str_src + i);
		i++;
	}
	return (str_dst);
}
