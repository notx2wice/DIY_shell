/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:18 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:43:11 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env(char *key)
{
	t_env *env;
	t_env *bef;
	t_env *next;

	env = g_all.env_first;
	bef = 0;
	while (env)
	{
		next = env->next;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (bef)
				bef->next = next;
			else
				g_all.env_first = next;
			free(env->key);
			if (env->value)
				free(env->value);
			free(env);
			break ;
		}
		bef = env;
		env = env->next;
	}
}

int		exec_unset(t_split_two *cmd)
{
	t_env	*env;
	int		i;

	env = g_all.env_first;
	i = 1;
	while (cmd->cmd[i])
	{
		remove_env(cmd->cmd[i]);
		i++;
	}
	return (0);
}
