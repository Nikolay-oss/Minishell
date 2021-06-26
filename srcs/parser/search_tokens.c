#include "ft_parser.h"

static t_uint	search_str_in_quotes(t_minishell *minishell, char *buf,
	char type)
{
	t_uint	i;
	t_bool	isopenquote;
	t_uint	idx_end;
	char	*str_noquotes;

	isopenquote = 1;
	i = 1;
	while (*(buf + i))
	{
		if (*(buf + i) == type)
			change_flag(&isopenquote);
		i++;
		if (!isopenquote && ft_memchr("|<> ", *(buf + i), 4))
			break ;
	}
	if (*(buf + i))
		idx_end = i - 2;
	else
		idx_end = i;
	str_noquotes = get_str_withoutquotes(buf + 1, type, idx_end);
	// нужен обработчик ошибок
	ft_push_back(minishell->commands, check_memory(&str_noquotes));
	return (i);
}

static t_uint	search_simple_args(t_minishell *minishell, char *buf)
{
	t_uint	i;
	t_uint	start;

	i = 0;
	start = 0;
	while (*(buf + i))
	{
		if (*(buf + i) == ' ')
		{
			add_command_to_list(minishell, buf + start, i - start);
			set_str_withvars(minishell, minishell->commands->tail->content);
			tilda_handler(minishell, &minishell->commands->tail->content);
			start = i;
		}
		start += skip_spaces(buf + i);
		if (start > i)
			i += start - i;
		if (ft_memchr("<>|\"'", *(buf + i), 5))
			break ;
		if (*(buf + i))
			i++;
	}
	if (!*(buf + i))
		add_command_to_list(minishell, buf + start, i - start);
	return (i);
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

static void	search_vars_in_str(t_minishell *minishell, char buf_chr, char c,
	t_bool type)
{
	if (buf_chr == c)
	{
		if (type)
			tilda_handler(minishell, &minishell->commands->tail->content);
		set_str_withvars(minishell, minishell->commands->tail->content);
	}
}

t_uint	search_tokens(t_minishell *minishell, char *buf)
{
	t_uint	i;

	i = skip_spaces(buf);
	if (*buf == '\'' || *buf == '"')
	{
		i += search_str_in_quotes(minishell, buf + i, *buf);
		search_vars_in_str(minishell, *buf, '"', 0);
	}
	else if (*(buf + i) == '>' || *(buf + i) == '<')
		i += search_redirects(minishell, buf + i, *(buf + i));
	else if (*(buf + i) == '|')
	{
		add_command_to_list(minishell, buf + i, i + 1 - i);
		i++;
	}
	else
	{
		i += search_simple_args(minishell, buf + i);
		search_vars_in_str(minishell, *(buf + i), 0, 1);
	}
	return (i);
}
