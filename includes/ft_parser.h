/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:34 by dkenchur          #+#    #+#             */
/*   Updated: 2021/06/22 21:41:45 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include "minishell.h"

void	ft_parser(t_minishell *minishell, char *buf);
t_uint	skip_spaces(char *str);
void	destroy_command_buf(char **command);
void	copy_command(char *buf, char **str_cmd, t_uint idx);
void	change_flag(t_bool *flag);

#endif
