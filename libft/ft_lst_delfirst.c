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
