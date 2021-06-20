#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "data_types.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include <limits.h> // It is allowed? use define from limits

typedef struct s_minishell
{
	t_list		*env;
	t_list		*hide_vars; // for variables in bash
}				t_minishell;

// region init
void	init_env(t_list **env, char **envp);
// end region

void	select_command(t_minishell *minishell, char **command);
t_node	*getvar_node(t_list *vars, const char *var_name);

// region builtins
void	ft_echo(char **command);
void	ft_env(t_list *env);
void	ft_cd(t_list *env, char *path);
int		ft_export(t_minishell *minishell, char **vars);
int		ft_pwd();
// end region

// region redirect
// ------only test!!!-------
void	ft_redir(char **command, char *str);
// end region

// region execve

// end region

// region history
// typedef struct s_history
// {
// 	t_list	*history;
// 	t_uint	max;
// }			t_history;
// end region

#endif
