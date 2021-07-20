/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:24:06 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/20 23:09:43 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bubble_sort(char **arr, t_uint size)
{
	t_uint	i;
	t_uint	j;
	t_bool	isswap;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		isswap = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(*(arr + j), *(arr + j + 1)) > 0)
			{
				tmp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = tmp;
				isswap = 1;
			}
			j++;
		}
		if (!isswap)
			break ;
		i++;
	}
}

static void	copy_vars(char **env_arr, t_list *vars, t_uint *idx)
{
	t_node	*node;

	node = vars->head;
	while (node)
	{
		*(env_arr + *idx) = (char *)node->content;
		(*idx)++;
		node = node->next;
	}
}

static int	create_env_arr(t_minishell *minishell, char **env_arr)
{
	t_uint	i;

	if (!env_arr)
		return (errno);
	i = 0;
	copy_vars(env_arr, minishell->env, &i);
	copy_vars(env_arr, minishell->env_secret, &i);
	return (0);
}

static void	print_declare_env_utils(char *var)
{
	char	*p_equal;

	p_equal = ft_strchr(var, '=');
	if (!p_equal)
		printf("declare -x %s\n", var);
	else
	{
		*p_equal = 0;
		printf("declare -x %s", var);
		*p_equal = '=';
		printf("=\"%s\"\n", ++p_equal);
	}
}

int	print_declare_env(t_minishell *minishell)
{
	char	**env_arr;
	t_uint	arr_size;
	t_uint	i;

	arr_size = (t_uint)(minishell->env->size + minishell->env_secret->size);
	env_arr = (char **)malloc((arr_size + 1) * sizeof(char *));
	if (create_env_arr(minishell, env_arr))
		return (errno);
	*(env_arr + arr_size) = NULL;
	bubble_sort(env_arr, arr_size);
	i = 0;
	while (*(env_arr + i))
	{
		print_declare_env_utils(*(env_arr + i));
		i++;
	}
	free(env_arr);
	return (0);
}
