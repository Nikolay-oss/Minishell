/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:01:51 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/15 06:51:03 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_tail(t_list *lst, t_node *cur, t_node *prev)
{
	if (cur == lst->tail)
	{
		lst->tail = prev;
		lst->tail->next = NULL;
	}
}

void	ft_del_node(t_list *lst, void (*del)(void*),
	t_node *node)
{
	t_node	*current;
	t_node	*prev;

	if (lst->size == 1)
		ft_lst_delfirst(lst, del);
	current = lst->head;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			lst->size--;
			check_tail(lst, current, prev);
			if (prev)
				prev->next = current->next;
			else
				lst->head = current->next;
			if (del)
				del(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}
