#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_types.h"
# include "commands_list.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
//# include <stdlib.h>
# include <limits.h> // It is allowed? use define from limits

# define STDIN	0
# define STDOUT	1
# define STDER	2

// region redirect
typedef struct s_stdstreams
{
	int	std_in;
	int	std_out;
}		t_stdstreams;
// end region

typedef struct s_minishell
{
	t_list			*env;
	t_list			*hide_vars; // for variables in bash
	t_list			*all_commands;
	t_list			*f_quotes;
	t_commands		*commands;
	t_stdstreams	stdstreams;
	t_uint			pipes_count;
	char			*home_path;
	char			*here_document;
	long long int	exit_status;
}					t_minishell;

//region global structure
typedef struct	s_signal
{
	t_bool	sig_int;
	t_bool	sig_quit;
}				t_signal;
//end region

// region file_exists
t_bool	file_exists(const char *filename);
// end region

// region errors_handler
void	print_error(char *str, int errorcode);
void	command_not_found(char *str, int errorcode);
void	syntax_error(char *token);
// end region

// region init
void	init_env(t_list **env, char **envp);
// end region

// region commands
void	select_command(t_minishell *minishell, char **command);
void	destroy_command_buf(char **command);
// region end

t_node	*getvar_node(t_list *vars, const char *var_name);
char	*getvar_value(t_list *vars, const char *var_name);
t_bool	file_exists(const char *filename);

// region builtins
void	ft_echo(char **command);
void	ft_env(t_list *env);
void	ft_cd(t_minishell *minishell, char *path);
void	ft_unset(t_list *env, char **var);
int		ft_export(t_minishell *minishell, char **vars);
int		ft_pwd();
void	ft_exit(t_minishell *minishell, char **var);
// end region

// region redirect
void	redir_handler(t_minishell *minishell, t_commands *node_cmd);
int		redir2_input(t_minishell *minishell, const char *stop_value,
					int f_quotes);
int		save_std_descriptors(t_stdstreams *stdstreams);
int		revert_std_descriptors(t_stdstreams *stdstreams);
// end region

// region execute
void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc);
void	save_path_to_bin(t_minishell *minishell, char *cmd_bin,
					char **cmd_bin_out);
void	make_path_to_bin(char *path, char *cmd_bin, char **cmd_bin_out);
// end region

// region history
// typedef struct s_history
// {
// 	t_list	*history;
// 	t_uint	max;
// }			t_history;
// end region

#endif
