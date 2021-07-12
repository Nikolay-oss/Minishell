#include "minishell.h"

void	destroy_shell(t_minishell *minishell)
{
	destroy_command_list(&minishell->commands, &destroy_arr2d);
	ft_lst_clear(&minishell->all_commands, &free);
	ft_lst_clear(&minishell->f_quotes, &free);
	ft_lst_clear(&minishell->env, &free);
	ft_lst_clear(&minishell->env_secret, &free);
	free(minishell->home_path);
	free(minishell);
}
