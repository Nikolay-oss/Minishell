/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:11:09 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:26:31 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	init_size(int n)
{
	size_t	size;

	if (n >= 0)
		size = 1;
	else
		size = 2;
	while (n / 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long long int	num;
	char			*str;
	size_t			size;

	size = init_size(n);
	num = n;
	str = (char *)ft_calloc(size + 1, 1);
	if (!str)
		return (str);
	if (num < 0)
	{
		num *= -1;
		*str = '-';
	}
	while (size > 0)
	{
		*(str + --size) = (num % 10) + '0';
		num /= 10;
		if (*(str + size - 1) == '-' && size == 1)
			break ;
	}
	return (str);
}
