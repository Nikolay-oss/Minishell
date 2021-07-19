/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 20:01:22 by brice             #+#    #+#             */
/*   Updated: 2021/07/19 23:38:22 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*alloc_int(char **cmd)
{
	int	*arr_new;
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (cmd[size])
		size++;
	arr_new = (int *)ft_calloc(size + 1, sizeof(int));
	if (!arr_new)
		return (NULL);
	while (i < size)
		arr_new[i++] = 0;
	arr_new[i] = 0;
	return (arr_new);
}

int	parser_cycle(char **cmd, int *arr, const int *i, const int *j)
{
	if ((ft_isdigit(cmd[*i][*j]) && *j == 0)
		|| (!cmd[*i][*j + 1] && cmd[*i][*j] == '$') || !is_env(cmd[*i][*j]))
	{
		arr[*i] = ERROR;
		return (ERROR);
	}
	else
		arr[*i] = 1;
	return (1);
}

int	*parser_commands(char **cmd)
{
	int	i;
	int	j;
	int	*arr;

	i = 1;
	arr = alloc_int(cmd);
	if (arr == NULL)
		return (NULL);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (parser_cycle(cmd, arr, &i, &j) == -1)
				break ;
			j++;
		}
		i++;
	}
	return (arr);
}

void	delete_node(t_minishell *minishell, char *var)
{
	t_node	*node;

	node = getvar_node(minishell->env, var);
	if (!node)
		return ;
	else
		ft_del_node(minishell->env, &free, node);
}

void	ft_unset(t_minishell *minishell, char **var)
{
	int	i;
	int	*ret;

	i = 1;
	ret = parser_commands(var);
	if (ret == NULL)
	{
		print_error("malloc", errno);
		g_signals.exit_status = errno;
		return ;
	}
	while (var[i])
	{
		if (ret[i] == ERROR)
			error_handler(var[i]);
		else
			delete_node(minishell, var[i]);
		i++;
	}
	free(ret);
}
