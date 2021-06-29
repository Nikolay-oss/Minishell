/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_command_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:34:06 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/29 20:17:01 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_list.h"
#include <stdlib.h>

void	destroy_command_list(t_commands **head, void (*del)(char **))
{
	t_commands	*cur_cmd;
	t_commands	*next_cmd;

	if (!*head)
		return ;
	cur_cmd = *head;
	while (cur_cmd)
	{
		next_cmd = cur_cmd->next;
		if (del)
			del(cur_cmd->cmd);
		free(cur_cmd);
		cur_cmd = next_cmd;
	}
	*head = NULL;
}
