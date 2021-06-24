#include "ft_parser.h"

t_uint	search_str_in_quotes(t_minishell *minishell, char *buf, char type)
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
	ft_push_back(minishell->commands, str_noquotes);
	return (i);
}

t_uint	search_simple_args(t_minishell *minishell, char *buf)
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

t_uint	search_redirects(t_minishell *minishell, char *buf, char type)
{
	t_uint	i;

	i = 0;
	if (*(buf + i + 1) == type)
		i += 1;
	add_command_to_list(minishell, buf, ++i);
	return (i);
}

t_uint	search_tokens(t_minishell *minishell, char *buf)
{
	t_uint	i;

	i = skip_spaces(buf);
	if (*buf == '\'' || *buf == '"')
		i += search_str_in_quotes(minishell, buf + i, *buf);
	else if (*(buf + i) == '>' || *(buf + i) == '<')
		i += search_redirects(minishell, buf + i, *(buf + i));
	else if (*(buf + i) == '|')
		add_command_to_list(minishell, buf, ++i);
	else
		i += search_simple_args(minishell, buf + i);
	return (i);
}

t_uint	search_vars(t_minishell *minishell, t_list **vars, char *cmd_str,
	t_uint *sizenovars)
{
	char	end_var;
	t_uint	i;
	t_uint	dollar_pos;
	t_uint	vars_count;

	i = 0;
	*sizenovars = 0;
	vars_count = 0;
	while (*(cmd_str + i))
	{
		if (*(cmd_str + i) == '$')
		{
			vars_count++;
			dollar_pos = i++;
			while (ft_isalpha(*(cmd_str + i)) && !ft_memchr(" =$'\"", *(cmd_str + i), 5))
				i++;
			end_var = *(cmd_str + i);
			*(cmd_str + i) = 0;
			save_var(minishell, vars, cmd_str + dollar_pos + 1);
			*(cmd_str + i) = end_var;
		}
		if (*(cmd_str + i) && *(cmd_str + i) != '$')
		{
			i++;
			(*sizenovars)++;
		}
	}
	return (vars_count);
}
