/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:43:19 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:22:20 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	ft_issign(const char c)
{
	if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

static int	select_sign(const char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long long int	res;
	unsigned long long int	max;
	int						i;
	int						sign;

	res = 0;
	i = 0;
	max = 922337203685477580;
	while (ft_isspace(*(str + i)))
		i++;
	sign = select_sign(*str);
	if (ft_issign(*str))
		i++;
	while (ft_isdigit(*(str + i)))
	{
		if ((res > max || (res == max && (*(str + i) - '0') > 7))
			&& sign == 1)
			return (-1);
		else if ((res > max || (res == max && (*(str + i) - '0') > 8))
			&& sign == -1)
			return (0);
		res = res * 10 + (*(str + i) - '0');
		i++;
	}
	return (sign * res);
}
