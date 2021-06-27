#include "ft_parser.h"

t_uint	get_endquote_idx(char *buf, char type)
{
	t_uint	i;
	t_bool	isopenquote;

	isopenquote = 1;
	i = 0;
	while (*(buf + i))
	{
		if (*(buf + i) == type)
			change_flag(&isopenquote);
		if (!isopenquote)
			break ;
		i++;
	}
	return (i);
}

static t_uint	search_arg(t_minishell *minishell, char *buf)
{
	t_uint	len;
	char	*arg;
	char	chr_old;

	len = 0;
	arg = NULL;
	while (!ft_memchr("<>| ", *(buf + len), 5))
	{
		if (ft_memchr("'\"", *(buf + len), 2))
		{
			len += get_endquote_idx(buf + len + 1, *(buf + len));
			len++;
		}
		if (*(buf + len))
			len++;
	}
	chr_old = *(buf + len);
	*(buf + len) = 0;
	arg_handler(minishell, &arg, buf, len);
	*(buf + len) = chr_old;
	if (arg)
		ft_push_back(minishell->commands, check_memory(&arg));
	return (len);
}

static t_uint	search_redirects(t_minishell *minishell, char *buf, char type)
{
	t_uint	i;

	i = 0;
	if (*(buf + i + 1) == type)
		i++;
	add_command_to_list(minishell, buf, ++i);
	return (i);
}

t_uint	search_tokens(t_minishell *minishell, char *buf)
{
	t_uint	i;
	char	*tilda;

	i = skip_spaces(buf);
	if (*(buf + i) == '>' || *(buf + i) == '<')
		i += search_redirects(minishell, buf + i, *(buf + i));
	else if (*(buf + i) == '~')
	{
		tilda = tilda_handler(minishell, buf + i);
		if (tilda)
		{
			ft_push_back(minishell->commands, tilda);
			i++;
		}
		else
			i += search_arg(minishell, buf + i);
	}
	else if (*(buf + i) == '|')
	{
		add_command_to_list(minishell, buf + i, i + 1 - i);
		i++;
	}
	else
		i += search_arg(minishell, buf + i);
	return (i);
}
