#include "libft.h"

int	ft_count_args(char **var)
{
	int i;

	i = 0;
	while (var[i])
		i++;
	return (i);
}
