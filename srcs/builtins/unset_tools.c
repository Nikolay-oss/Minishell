/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 20:02:07 by brice             #+#    #+#             */
/*   Updated: 2021/07/18 20:03:18 by brice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_str(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, 2);
	if (str2 != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str2, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str3, 2);
}

void	error_handler(char *var)
{
	char	*arg;
	char	*arg_sec;

	arg = ft_strjoin("`", var);
	arg_sec = ft_strjoin(arg, "\'");
	print_error_str("unset", arg_sec, "not a valid identifier");
	free(arg);
	free(arg_sec);
	signals.exit_status = 1;
}

int	is_env(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c == '_')
		return (1);
	else if (ft_isdigit(c))
		return (1);
	else
		return (0);
}
