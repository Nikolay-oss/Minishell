#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct s_minishell
{
	t_list		*env;
}				t_minishell;

// region init
void	init_env(t_list **env, char **envp);
// end region

void	select_command(t_minishell *minishell, char **command);

// region builtins
void	ft_echo(char **command);
void	ft_env(t_list *env);
// end region

// region execve

// end region

#endif
