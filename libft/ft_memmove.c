/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:21:29 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:27:23 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str_dst;
	unsigned char	*str_src;

	if (dst == src)
		return (dst);
	str_dst = (unsigned char *)dst;
	str_src = (unsigned char *)src;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			*(str_dst + len) = *(str_src + len);
		}
	}
	else
		str_dst = ft_memcpy(dst, src, len);
	return (str_dst);
}
