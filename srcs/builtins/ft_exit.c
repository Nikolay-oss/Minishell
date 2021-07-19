#include "minishell.h"

static int	ft_is_string_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_return_value(t_minishell *minishell)
{
	int	res;

	res = (int)((minishell->exit_status) % 256);
	printf("exit\n");
	exit(res);
}

static void	ft_print_error(int c, char *var)
{
	printf("exit\nminishell: exit: %s: numeric argument required\n", var);
	exit(c);
}

static void	ft_exit_handler(t_minishell *minishell, char **var,
							int *i, int *flag)
{
	int	res;

	if (var[*i] && ft_count_args(var) <= 2)
	{
		res = ft_is_string_digit(var[*i]);
		if (res == 0 && *i == 1)
			ft_print_error(2, var[*i]);
		else if (res == 1 && (int)ft_strlen(var[*i]) > 19)
			ft_print_error(2, var[*i]);
		else if (res == 1 && (int)ft_strlen(var[*i]) <= 19)
		{
			minishell->exit_status = ft_atoi(var[*i]);
			if ((int)(minishell->exit_status) == 0 && *var[*i] != '0')
				ft_print_error(2, var[*i]);
			ft_return_value(minishell);
		}
	}
	if (!*flag)
		exit((int)minishell->exit_status);
	else if (*flag == 2 && ft_count_args(var) > 2)
		exit(*flag);
}

void	ft_exit(t_minishell *minishell, char **var)
{
	int			i;
	static int	flag;

	minishell->exit_status = g_signals.exit_status;
	i = 1;
	if (flag == 1)
		exit(1);
	if (ft_count_args(var) > 2)
	{
		if (ft_is_string_digit(var[i]))
		{
			printf("exit\nminishell: exit: too many arguments\n");
			flag = 1;
		}
		else
		{
			printf("exit\nminishell: exit: %s: a"
				   "numeric argument is required\n", var[i]);
			flag = 2;
		}
	}
	ft_exit_handler(minishell, var, &i, &flag);
}
