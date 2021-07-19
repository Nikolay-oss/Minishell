/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:24:34 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/20 00:38:52 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include "minishell.h"

/**
 * region ft_parser
**/
void	ft_parser(t_minishell *minishell, char *buf);
t_bool	add_to_f_quotes(t_minishell *minishell, int flag);
int		add_arg(t_minishell *minishell, char **arg, char *buf);
t_bool	add_pipe_ehandler(t_minishell *minishell, char *buf);
/**
 * end region
**/

/**
 * region ft_parser
**/
void	commands_handler(t_minishell *minishell);
/**
 * end region
**/

/**
 * region ft_parser
**/
t_bool	analyzer(t_minishell *minishell);
/**
 * end region
**/

/**
 * region ft_parser
**/
t_uint	skip_spaces(char *str);
t_bool	add_command_to_allcommands(t_minishell *minishell, char *buf,
			t_uint idx);
void	change_flag(t_bool *flag);
t_bool	check_memory(t_minishell *minishell, void *str);
void	init_range(t_uint *start, t_uint *end, t_uint s_val, t_uint e_val);
/**
 * end region
**/

/**
 * region ft_parser
**/
t_uint	search_tokens(t_minishell *minishell, char *buf);
t_uint	get_endquote_idx(char *buf, char type);
/**
 * end region
**/

/**
 * region ft_parser
**/
void	arg_handler(t_minishell *minishell, char **arg, char *buf, t_uint len);
/**
 * end region
**/

/**
 * region ft_parser
**/
void	init_vars_in_split_into_vars(char **str, t_uint *start, t_uint *end);
char	*get_str_withvars(t_minishell *minishell, char *str);
t_bool	search_var_value(t_minishell *minishell, char **var, t_node *node);
char	*tilda_handler(t_minishell *minishell, char *str);
void	check_last_var(t_minishell *minishell, t_list **str_parts, char *str,
			t_uint end);
/**
 * end region
**/

/**
 * region ft_parser
**/
t_bool	isredir(const char c);
t_bool	ispipe(const char c);
/**
 * end region
**/

#endif
