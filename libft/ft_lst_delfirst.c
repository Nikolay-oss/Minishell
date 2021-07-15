/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_delfirst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:01:56 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/15 06:51:30 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_delfirst(t_list *lst, void (*del)(void*))
{
	if (lst->head && del)
	{
		del(lst->head->content);
		free(lst->head);
		lst->head = NULL;
		lst->size--;
		if (!lst->size)
			lst->tail = NULL;
	}
}
