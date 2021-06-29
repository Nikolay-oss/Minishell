/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:33:27 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/29 19:33:28 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_LIST_H
# define COMMANDS_LIST_H

typedef struct s_commands
{
	struct s_commands	*next;
	char				**cmd;
}						t_commands;

void	add_to_command_list(t_commands **head, char **cmd);
void	destroy_command_list(t_commands **head, void (*del)(char **));

#endif
