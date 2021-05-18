/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_not_built_in_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:11:53 by ukim              #+#    #+#             */
/*   Updated: 2021/05/17 22:34:42 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	chk_is_cmd_path(t_split_two *cmd)
{
	if (!ft_strncmp(cmd->cmd[0], "/", 1) ||
		!ft_strncmp(cmd->cmd[0], "./", 2))
		cmd->ispath = 1;
}

char	**get_path_env(void)
{
	t_env	*env;
	char	**path;
	char	*env_path;

	env = g_all.env_first;
	env_path = 0;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			env_path = env->value;
		env = env->next;
	}
	if (!env_path)
		return (0);
	path = ft_split(env_path, ':');
	return (path);
}

char	**make_env_char(void)
{
	t_env	*env;
	char	**res;
	char	*tmp;
	int		size;
	int		i;

	env = g_all.env_first;
	size = chk_arg_cnt_env();
	res = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env)
	{
		if (!env->value)
		{
			env = env->next;
			continue;
		}
		tmp = ft_strjoin(env->key, "=");
		res[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
	res[i] = 0;
	return (res);
}

void	exec_not_builtin_sub(t_split_two *cmd, char **path)
{
	char	*tmp;
	char	*path_arg;
	char	**env_arg;
	int		i;

	i = -1;
	while (path && path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		path_arg = ft_strjoin(tmp, cmd->cmd[0]);
		env_arg = make_env_char();
		execve(path_arg, cmd->cmd, env_arg);
		free(tmp);
		free(path_arg);
		free_2d_arr(&env_arg);
	}
}

void	exec_not_builtin(t_split_two *cmd)
{
	char	**path;

	change_redir(cmd);
	chk_is_cmd_path(cmd);
	if (cmd->ispath == 0)
	{
		if (!(path = get_path_env()))
			exit(no_file_error(cmd, 127));
		exec_not_builtin_sub(cmd, path);
		free_2d_arr(&path);
		//exit(no_cmd_error(cmd, 127));
		exit(0);
	}
	else
	{
		execve(cmd->cmd[0], cmd->cmd, make_env_char());
		exit(no_file_error(cmd, 127));
	}
}