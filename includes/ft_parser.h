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
void	add_command_to_list(t_minishell *minishell, char *buf, t_uint idx);
void	change_flag(t_bool *flag);
char	*check_memory(char **str);
// end region

// region search_tokens
t_uint	search_tokens(t_minishell *minishell, char *buf);
t_uint	get_endquote_idx(char *buf, char type);
// end region

// region arg_handler
void	arg_handler(t_minishell *minishell, char **arg, char *buf, t_uint len);
// end region

// region vars_handler
char	*get_str_withvars(t_minishell *minishell, char *str);
void	search_var_value(t_minishell *minishell, char **var, t_node *node);
char	*tilda_handler(t_minishell *minishell, char *str);
// end region

// region check_tokens
t_bool	isredir(const char c);
t_bool	ispipe(const char c);
// end region

#endif
