/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:10:58 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:27:50 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_back(t_list *lst, void *data)
{
	t_node	*new;

	new = ft_create_node(data);
	if (!new)
		return ;
	if (!lst->tail)
	{
		lst->head = new;
		lst->tail = new;
		lst->size++;
		return ;
	}
	lst->tail->next = new;
	lst->tail = new;
	lst->size++;
}
