/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:24:13 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/13 21:24:14 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd()
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (path)
	{
		ft_putendl_fd(path, 1);
		free(path);
		return (0);
	}
	return (1);
}
