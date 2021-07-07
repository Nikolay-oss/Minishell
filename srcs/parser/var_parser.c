#include "minishell.h"

t_bool	var_parser(char *str)
{
	t_uint	i;
	t_bool	num_flag;
	t_bool	isvar;

	if (*str == '=')
		return (0);
	num_flag = 0;
	isvar = 1;
	i = 0;
	while (*(str + i) && *(str + i) != '=')
	{
		if (ft_isalpha(*(str + i)) || *(str + i) == '_')
			num_flag = 1;
		else if (!num_flag && ft_isdigit(*(str + i)))
		{
			isvar = 0;
			break ;
		}
		else
			break ;
		i++;
	}
	return (isvar);
}
