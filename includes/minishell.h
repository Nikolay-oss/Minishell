/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 00:40:11 by dkenchur          #+#    #+#             */
/*   Updated: 2021/07/20 00:40:12 by dkenchur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_types.h"
# include "commands_list.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# define ERROR			(-1)
# define ERR_SIGNAL		(1)
# define FPERMISSIONS	0666
# define HEREDOCNAME	".heredoc"

# define PROMPT "\033[0;32mprompt> \033[0m"

/**
 * region redirect
**/
typedef struct s_stdstreams
{
	int	std_in;
	int	std_out;
}		t_stdstreams;
/**
 * end region
**/

/**
 * region shell
**/
typedef struct s_minishell
{
	t_list			*env;
	t_list			*env_secret;
	t_list			*all_commands;
	t_list			*f_quotes;
	t_commands		*commands;
	t_stdstreams	stdstreams;
	t_uint			pipes_count;
	t_bool			ismem_error;
	char			*home_path;
	char			*old_pwd;
	char			*pwd;
	char			update_pwd;
	char			**heredocs;
	long long int	exit_status;
	pid_t			pid;
	int				flag;
	int				fd_old;
	int				cnt_prcs;
	int				flag_cd;
}					t_minishell;

void	shell_handler(t_minishell *minishell);
t_bool	init_shell(t_minishell *minishell, char **envp);
void	destroy_shell(t_minishell *minishell);
/**
 * end region
**/

/**
 * region g_signals
**/
typedef struct s_signal
{
	pid_t	pid;
	int		exit_status;
}				t_signal;

extern t_signal	g_signals;

void	ft_signals(int sig);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	save_status(int status);
/**
 * end region
**/

/**
 * region file_exists
**/
t_bool	file_exists(const char *filename);
/**
 * end region
**/

/**
 * region errors_handler
**/
void	print_error(char *str, int errorcode);
void	command_not_found(char *str, int errorcode);
void	syntax_error(char *token);
void	ft_malloc_error(t_minishell *minishell);
t_bool	search_arg_ehandler(t_minishell *minishell, int isquotes, char **arg,
			char *buf);
void	dup_ehandler(void);
/**
 * end region
**/

/**
 * region commands
**/
void	select_command(t_minishell *minishell, char **command, t_bool newproc);
void	destroy_arr2d(char **command);
/**
 * end region
**/

t_node	*getvar_node(t_list *vars, const char *var_name);
char	*getvar_value(t_minishell *shell, t_list *vars, const char *var_name);

/**
 * region builtins
**/
int		ft_echo(char **command);
int		ft_env(t_list *env);
void	ft_cd(t_minishell *minishell, char *path);
void	print_error_cd(void *str1, void *str2, int err);
int		pwd_error(char **current_pwd, char *path);
int		else_argument(t_minishell *minishell, t_node *curr_pwd, char **path);
void	ft_unset(t_minishell *minishell, char **var);

void	print_error_str(char *str1, char *str2, char *str3);
int		*alloc_int(char **cmd);
void	error_handler(char *var);
int		is_env(int c);

int		ft_export(t_minishell *minishell, char **vars);
int		print_declare_env(t_minishell *minishell);
t_bool	var_parser(char *str);
int		add_var(t_minishell *minishell, char *var, t_uint var_type);

int		ft_pwd(void);
void	ft_exit(t_minishell *minishell, char **var);
/**
 * end region
**/

/**
 * region redirect
**/
t_bool	redir_handler(t_minishell *minishell, t_commands *node_cmd, int n_proc,
			t_bool newproc);
t_bool	redir2_input(t_minishell *minishell, const char *stop_value,
			int f_quotes, const char *filename);
t_bool	save_std_descriptors(t_stdstreams *stdstreams);
t_bool	revert_std_descriptors(t_stdstreams *stdstreams);
t_bool	update_cmd_buf(char **cmd, int redir_pos, char ***cmd_new);
int		ft_redir(const char *filename, int o_flags, int s_flags,
			t_bool dir_type);
t_bool	redir_dual_input(t_minishell *minishell, t_commands *node_cmd,
			const char *filename);
t_bool	heredocs_handler(t_minishell *minishell);
void	destroy_heredocs(t_minishell *minishell);
t_bool	launch_dual_redir(t_minishell *minishell, int n_proc);
/**
 * end region
**/

/**
 * region pipes
**/
void	ft_pipes(t_minishell *minishell, t_commands *node, int fd_old);
/**
 * end region
**/

/**
 * region execute
**/
void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc);
void	save_path_to_bin(t_minishell *minishell, char *cmd_bin,
			char **cmd_bin_out);
void	make_path_to_bin(t_minishell *minishell, char *path, char *cmd_bin,
			char **cmd_bin_out);
/**
 * end region
**/

#endif
