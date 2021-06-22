#ifndef FT_PARSER_H
# define FT_PARSER_H
# include "minishell.h"

void	ft_parser(t_minishell *minishell, char *buf);
void	destroy_command_buf(char **command);

#endif
