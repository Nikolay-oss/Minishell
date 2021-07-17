#include "minishell.h"

//void	ft_cd_handler(char **buf, t_node *node, t_node *node_old, t_list *env, t_minishell *minishell)
//{
//	int		i;
//	char 	*swap;
//	(*buf) = getcwd(NULL, PATH_MAX); 							// protect
//	if (!(*buf))
//	{
//		print_error("getcwd", errno);
//		signals.exit_status = 1;
//		return ;
//	}
//	node_old = getvar_node(env, "OLDPWD");
//	if (!node_old && !minishell->old_pwd)
//	{
//		ft_push_back(env, ft_strjoin("OLDPWD=",
//									 getcwd(NULL, PATH_MAX)));
//		node_old = getvar_node(env, "OLDPWD");
//	}
//	free(node_old->content);
//	i = ft_get_index_symbol(node->content, '=');
//	if (!minishell->old_pwd)
//		node_old->content = (void *)ft_strjoin("OLDPWD=", (node->content + ++i)); // free
//	free(node->content);
//	if (!minishell->pwd)
//		node->content = (void *)ft_strjoin("PWD=", (*buf));  // edit
//	free((*buf));
//	swap = (char *)minishell->old_pwd; // pwd
//	minishell->old_pwd = minishell->pwd;
//	minishell->pwd = swap;
//
//	signals.exit_status = 0;
//}

void update_path(int arg, t_minishell *minishell, char **path)
{

}

void	ft_cd(t_minishell *minishell, char *path)
{
	int		res;
	char	*buf;
	t_node	*node;
	t_node *node_old;

	if (!path)
		update_path(0, minishell, &path);
	if(!ft_strcmp(path, "-"))
		update_path(1, minishell, &path);

}
