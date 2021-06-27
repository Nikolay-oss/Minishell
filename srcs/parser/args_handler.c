#include "ft_parser.h"

static void	add_to_arg(char **arg, char *new_arg)
{
	char	*tmp;

	if (*arg)
	{
		tmp = *arg;
		*arg = ft_strjoin(*arg, new_arg);
		free(tmp);
	}
	else
		*arg = ft_strdup(new_arg);
	if (!*arg)
		; // error
}

static void	simple_arg_handler(t_minishell *minishell, char **arg, char *buf)
{
	char	*new_arg;

	new_arg = get_str_withvars(minishell, buf);
	if (new_arg)
	{
		add_to_arg(arg, new_arg);
		free(new_arg);
	}
	else
		add_to_arg(arg, buf);
}

static t_uint	quote_handler(t_minishell *minishell, char **arg, char *buf, char type)
{
	t_uint	i;
	char	chr_old;

	i = get_endquote_idx(buf, type);
	if (i > 0)
	{
		chr_old = *(buf + i);
		*(buf + i) = 0;
		if (type == '\"')
			simple_arg_handler(minishell, arg, buf);
		else
			add_to_arg(arg, buf);
		*(buf + i) = chr_old;
	}
	if (*(buf + i) == type)
		i++;
	return (i);
}

static void	arg_handler_tool(char *buf, t_uint *i_end, char *quote_type)
{
	while (!ft_memchr("\"'", *(buf + *i_end), 3))
			(*i_end)++;
	*quote_type = *(buf + *i_end);
}

void	arg_handler(t_minishell *minishell, char **arg, char *buf, t_uint len)
{
	t_uint	i_start;
	t_uint	i_end;
	char	quote_type;
	char	*p_quote;

	i_start = 0;
	i_end = 0;
	while (i_start < len)
	{
		arg_handler_tool(buf, &i_end, &quote_type);
		if (i_end > i_start)
		{
			p_quote = (buf + i_end);
			*(buf + i_end) = 0;
			simple_arg_handler(minishell, arg, buf + i_start);
			i_end += quote_handler(minishell, arg, buf + i_end, quote_type);
			*p_quote = quote_type;
		}
		else
		{
			if (i_end < len)
				i_end++;
			i_end += quote_handler(minishell, arg, buf + i_end, quote_type);
		}
		i_start = i_end;
	}
}
