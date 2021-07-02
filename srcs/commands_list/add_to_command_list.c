/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:33:25 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/29 20:14:59 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_list.h"
#include <stdlib.h>

void	add_to_command_list(t_commands **head, char **cmd, int *flags)
{
	t_commands	*new_cmd;
	t_commands	*cur_cmd;

	new_cmd = (t_commands *)malloc(sizeof(t_commands));
	if (!new_cmd)
		return ; // error
	new_cmd->cmd = cmd;
	new_cmd->flags_quotes = flags;
	new_cmd->next = NULL;
	if (!*head)
		*head = new_cmd;
	else
	{
		cur_cmd = *head;
		while (cur_cmd->next)
			cur_cmd = cur_cmd->next;
		cur_cmd->next = new_cmd;
	}
}
