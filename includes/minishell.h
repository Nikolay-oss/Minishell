#ifndef MINISHELL_H
# define MINISHELL_H

void	select_command(char **command);

// region builtins
void	ft_echo(char **command);
void	ft_cd(char *path);
// end region

// region execve

// end region

#endif
