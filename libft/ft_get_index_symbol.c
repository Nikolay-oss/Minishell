#include "libft.h"

int	ft_get_index_symbol(char *str, char find)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == find)
			return i;
		i++;
	}
	return (-1);
}