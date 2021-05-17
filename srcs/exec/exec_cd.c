/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:03 by ukim              #+#    #+#             */
/*   Updated: 2021/05/03 18:29:15 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	if (!(new = (t_env *)malloc(sizeof(t_env) * 1)))
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

char	*lst_find_env(char *key)
{
	t_env *env;

	env = g_all.env_first;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	lst_change_add_env(char *key, char *value)
{
	t_env	*env;
	t_env	*last;

	env = g_all.env_first;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			if (env->value)
				free(env->value);
			if (value)
				env->value = strdup(value);
			return ;
		}
		last = env;
		env = env->next;
	}
	last->next = new_env(key, value);
	last = last->next;
}

int		exec_cd(t_split_two *cmd)
{
	char *val;
	char cwd[BUFFS];

	if (cmd->cmd[1] == NULL)
		val = lst_find_env("HOME");
	else
		val = cmd->cmd[1];
	if (!val || val[0] == '\0')
		return (no_home_error(cmd, 1));
	if (chdir(val) == -1)
		return (no_file_error(cmd, 1));
	if (ft_strlen(val) > BUFFS)
		return (-1);
	else
		lst_change_add_env("PWD", getcwd(cwd, BUFFS));
	return (0);
}
