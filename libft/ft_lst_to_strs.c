/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:02:04 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 22:02:05 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	strs_free(char **strs)
{
	size_t	i;

	i = 0;
	while (*(strs + i))
		free(*(strs + i++));
	free(strs);
}

static int	check_mem(char **strs, size_t idx)
{
	if (!*(strs + idx))
	{
		strs_free(strs);
		return (0);
	}
	return (1);
}

char	**ft_lst_to_strs(t_list *lst)
{
	char	**strs;
	t_node	*node;
	size_t	i;

	if (lst->size == 0)
		return (NULL);
	strs = (char **)ft_calloc(lst->size + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	node = lst->head;
	i = 0;
	while (i < lst->size)
	{
		if (node->content)
		{
			*(strs + i) = ft_strdup(node->content);
			if (!check_mem(strs, i))
				return (NULL);
		}
		node = node->next;
		i++;
	}
	return (strs);
}
