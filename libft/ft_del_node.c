#include "libft.h"

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
