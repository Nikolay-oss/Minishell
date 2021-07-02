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

static void	add_arg(t_minishell *minishell, char **arg, char *buf)
{
	if (!*arg && (!ft_strcmp(buf, "\"\"") || !ft_strcmp(buf, "''")))
		*arg = ft_strdup("");
	if (*arg)
		ft_push_back(minishell->all_commands, *arg);
	else
		minishell->exit_status = errno;
}

static t_uint	search_arg(t_minishell *minishell, char *buf, char **arg)
{
	t_uint	len;
	char	chr_old;
	t_bool	isquotes;

	len = 0;
	isquotes = 0;
	while (!ft_memchr("<>| ", *(buf + len), 5))
	{
		if (ft_memchr("'\"", *(buf + len), 2))
		{
			isquotes = 1;
			len += get_endquote_idx(buf + len + 1, *(buf + len));
			len++;
		}
		if (*(buf + len))
			len++;
	}
	chr_old = *(buf + len);
	*(buf + len) = 0;
	add_to_f_quotes(minishell, isquotes);
	arg_handler(minishell, arg, buf, len);
	add_arg(minishell, arg, buf);
	*(buf + len) = chr_old;
	return (len);
}

static t_uint	search_redirects(t_minishell *minishell, char *buf, char type)
{
	t_uint	i;

	i = 0;
	if (*(buf + i + 1) == type)
		i++;
	add_command_to_allcommands(minishell, buf, ++i);
	add_to_f_quotes(minishell, 0);
	return (i);
}

t_uint	search_tokens(t_minishell *minishell, char *buf)
{
	t_uint	i;
	char	*arg;

	arg = NULL;
	i = skip_spaces(buf);
	if (*(buf + i) == '>' || *(buf + i) == '<')
		i += search_redirects(minishell, buf + i, *(buf + i));
	else if (*(buf + i) == '~')
	{
		arg = tilda_handler(minishell, buf + i);
		if (arg)
			i++;
		i += search_arg(minishell, buf + i, &arg);
	}
	else if (*(buf + i) == '|')
	{
		add_command_to_allcommands(minishell, buf + i, i + 1 - i);
		add_to_f_quotes(minishell, 0);
		i++;
	}
	else
		i += search_arg(minishell, buf + i, &arg);
	return (i);
}
