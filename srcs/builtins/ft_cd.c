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

void print_error_cd(void *str1, void *str2, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, 2);
	if (str2 != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str2, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
}

void swap_cd()
{

}

void	update_cd(t_minishell *minishell, t_node *node, char **cwd, int index, char *str)
{
	node =	getvar_node(minishell->env, str);
	if (node)
	{
		index = ft_get_index_symbol(node->content, '=');
		add_var(minishell, ft_strjoin("OLDPWD=", (node->content + index + 1)), 1);
	}
	add_var(minishell, ft_strjoin("PWD=", *cwd), 1);
	free(*cwd);
}

void	update_path(int arg, t_minishell *minishell, char **path)
{
	t_node *node = NULL;
	t_node *node_old = NULL;
	char *cwd;
	int index;

	if (arg == 0)
	{
		node = getvar_node(minishell->env, "HOME");

		if (!node)
		{
			print_error_str("cd", NULL, "HOME not set");
			signals.exit_status = ERR_SIGNAL;
			return;
		}
		else
		{
			index = ft_get_index_symbol(node->content, '=');
			cwd = getcwd(NULL, PATH_MAX);
			if (cwd)
			{
//				update_cd(minishell, node, cwd, index, "PWD");
				if (chdir(((char *)node->content) + index + 1) == -1)
				{
					print_error("cd", errno);
					return;
				}
//				update_cd(minishell, node, &cwd, index, "PWD");
				node =	getvar_node(minishell->env, "PWD");
				if (node)
				{
					index = ft_get_index_symbol(node->content, '=');
					add_var(minishell, ft_strjoin("OLDPWD=", (node->content + index + 1)), 1);
				}
				add_var(minishell, ft_strjoin("PWD=", cwd), 1);
				free(cwd);
			}
		}
	}
	else if (arg == 1)
	{
		swap_cd();
	}
	else if (arg == 2)
	{
		node = getvar_node(minishell->env, "PWD");
		if (chdir(*path) == -1)
		{
			print_error_cd("cd", *path, errno);
			signals.exit_status = 1;
		}
		if (!node)
		{
			ft_del_node(minishell->env, free, node); //free node ?
			add_var(minishell, ft_strjoin("OLDPWD=", ""), 1);
		}
		else
		{
			index = ft_get_index_symbol(node->content, '=');
			cwd = getcwd(NULL, PATH_MAX);
			if(cwd)
			{
				node_old = getvar_node(minishell->env, "OLDPWD");
//				update_cd(minishell, node_old, &cwd, index, "OLDPWD");
				if (node_old)
				{
					index = ft_get_index_symbol(node->content, '=');
					add_var(minishell, ft_strjoin("OLDPWD=", &(node->content)[index + 1]), 1);
				}
				add_var(minishell, ft_strjoin("PWD=", cwd), 1);
				free(cwd);
			}
			else
			{
				print_error_cd("cd", path, errno);
				signals.exit_status = 1;
			}
		}
	}
}


void	ft_cd(t_minishell *minishell, char *path)
{
	int		res;
	char	*buf;
	t_node	*node;
	t_node *node_old;

	if (!path || !ft_strcmp(path, "~"))
		update_path(0, minishell, &path);
	else if(!ft_strcmp(path, "-"))
		update_path(1, minishell, &path);
	else
		update_path(2, minishell, &path);
}
