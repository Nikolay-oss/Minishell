#include "libft.h"

static void	strs_free(char **strs)
{
	size_t	i;

	i = 0;
	while (*(strs + i))
		free(*(strs + i++));
	free(strs);
}

char	**ft_lst_to_strs(t_list *lst)
{
	char	**strs;
	t_node	*node;
	size_t	i;

	if (!lst->head)
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
			if (!*(strs + i))
			{
				strs_free(strs);
				return (NULL);
			}
		}
		node = node->next;
		i++;
	}
	return (strs);
}
