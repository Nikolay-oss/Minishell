#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_types.h"
#include "commands_list.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
//# include <stdlib.h>
# include <limits.h> // It is allowed? use define from limits

typedef struct s_minishell
{
	t_list			*env;
	t_list			*hide_vars; // for variables in bash
	t_list			*all_commands;
	t_commands		*commands;
	char			*home_path;
	long long int	exit_status;
}					t_minishell;

//region global structure
typedef struct	s_signal
{
	t_bool	sig_int;
	t_bool	sig_quit;
}				t_signal;
//end region

// region init
void	init_env(t_list **env, char **envp);
// end region

// region commands
void	select_command(t_minishell *minishell, char **command);
// region end

t_node	*getvar_node(t_list *vars, const char *var_name);
char	*getvar_value(t_list *vars, const char *var_name);

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
// ------only test!!!-------
void	ft_redir(char **command, char *str);
// end region

// region execve
void	ft_exec(t_list *env, char **arv);
// end region

// region history
// typedef struct s_history
// {
// 	t_list	*history;
// 	t_uint	max;
// }			t_history;
// end region

#endif
