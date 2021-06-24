#include "libft.h"

char	*ft_lst_to_str(t_list *lst)
{
	char	*str;
	char	*tmp;
	t_node	*node;

	if (!lst->head)
		return (NULL);
	str = "";
	if (lst->head->content)
		str = ft_strjoin("", lst->head->content);
	if (!str)
		return (NULL);
	node = lst->head->next;
	while (node)
	{
		if (node->content)
		{
			tmp = str;
			str = ft_strjoin(str, node->content);
			free(tmp);
			if (!str)
				return (NULL);
		}
		node = node->next;
	}
	return (str);
}
