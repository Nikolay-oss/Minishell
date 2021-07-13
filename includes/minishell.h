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

// ------to delete------
// # define STDIN	0
// # define STDOUT	1
// # define STDER	2
// ----------

# define FPERMISSIONS 0666
# define HEREDOCNAME ".heredoc"

# define PROMPT "\033[0;32mprompt> \033[0m"

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
	t_list			*env_secret;
	t_list			*all_commands;
	t_list			*f_quotes;
	t_commands		*commands;
	t_stdstreams	stdstreams;
	t_uint			pipes_count;
	t_bool			ismem_error;
	char			*home_path;
	char			**heredocs;
	long long int	exit_status;
	pid_t 			pid;
	int				flag;
	int				cnt_prcs;
}					t_minishell;

//region global structure
typedef struct	s_signal
{
	t_bool	sig_int;
	t_bool	sig_quit;
}				t_signal;
//end region

// region shell_handler
void	shell_handler(t_minishell *minishell);
// end region

// region file_exists
t_bool	file_exists(const char *filename);
// end region

// region errors_handler
void	print_error(char *str, int errorcode);
void	command_not_found(char *str, int errorcode);
void	syntax_error(char *token);
void	ft_malloc_error(t_minishell *minishell);
t_bool	search_arg_ehandler(t_minishell *minishell, int isquotes, char **arg,
					char *buf);
void	dup_ehandler(t_minishell *minishell);
// end region

// region init
t_bool	init_shell(t_minishell *minishell, char **envp);
// end region

// region destroy
void	destroy_shell(t_minishell *minishell);
// end region

// region commands
void	select_command(t_minishell *minishell, char **command, t_bool newproc);
void	destroy_arr2d(char **command);
// region end

t_node	*getvar_node(t_list *vars, const char *var_name);
char	*getvar_value(t_minishell *shell, t_list *vars, const char *var_name);

// region builtins
int		ft_echo(char **command);
int		ft_env(t_list *env);
void	ft_cd(t_minishell *minishell, char *path);
void	ft_unset(t_list *env, char **var);
// subregion export
int		ft_export(t_minishell *minishell, char **vars);
int		print_declare_env(t_minishell *minishell);
t_bool	var_parser(char *str);
// end subregion
int		ft_pwd();
void	ft_exit(t_minishell *minishell, char **var);
// end region

// region redirect
t_bool	redir_handler(t_minishell *minishell, t_commands *node_cmd, int n_proc,
					t_bool newproc);
t_bool	redir2_input(t_minishell *minishell, const char *stop_value,
					int f_quotes, const char *filename);
t_bool	save_std_descriptors(t_stdstreams *stdstreams);
t_bool	revert_std_descriptors(t_stdstreams *stdstreams);
t_bool	update_cmd_buf(char **cmd, int redir_pos, char ***cmd_new);
int		ft_redir(const char *filename, int o_flags, int s_flags, t_bool dir_type);
t_bool	redir_dual_input(t_minishell *minishell, t_commands *node_cmd,
					const char *filename);
t_bool	heredocs_handler(t_minishell *minishell);
void	destroy_heredocs(t_minishell *minishell);
t_bool	launch_dual_redir(t_minishell *minishell, int n_proc);
// end region

// region pipes
void	ft_pipes(t_minishell *minishell, t_commands *node, int fd_old);
//void exec_pipeline(t_minishell *minishell, t_commands *cmds, int pos, int in_fd);
// end region

// region execute
void	ft_exec(t_minishell *minishell, char **cmd, t_bool create_proc);
void	save_path_to_bin(t_minishell *minishell, char *cmd_bin,
					char **cmd_bin_out);
void	make_path_to_bin(t_minishell *minishell, char *path, char *cmd_bin,
					char **cmd_bin_out);
// end region

#endif
