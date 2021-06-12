/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:44:30 by dkenchur          #+#    #+#             */
/*   Updated: 2021/04/25 01:28:07 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_front(t_list *lst, void *data)
{
	t_node	*node;

	node = ft_create_node(data);
	if (!node)
		return ;
	if (!lst->head)
	{
		lst->head = node;
		lst->tail = node;
		lst->size++;
		return ;
	}
	node->next = lst->head;
	lst->head = node;
	lst->size++;
}
