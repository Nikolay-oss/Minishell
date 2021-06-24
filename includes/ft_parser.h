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

// region utils
t_uint	skip_spaces(char *str);
void	destroy_command_buf(char **command);
void	add_command_to_list(t_minishell *minishell, char *buf, t_uint idx);
void	change_flag(t_bool *flag);
char	*get_str_withoutquotes(char *str, char quotetype, t_uint end_idx);
// end region

// region search_tokens
t_uint	search_str_in_quotes(t_minishell *minishell, char *buf, char type);
t_uint	search_simple_args(t_minishell *minishell, char *buf);
t_uint	search_redirects(t_minishell *minishell, char *buf, char type);
t_uint	search_tokens(t_minishell *minishell, char *buf);
t_uint	search_vars(t_minishell *minishell, t_list **vars, char *cmd_str,
			t_uint *sizenovars);
// end region

// region vars_handler

// end region

// region check_tokens
t_bool	isredir(const char c);
t_bool	ispipe(const char c);
// end region

#endif
