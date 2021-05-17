/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:13:45 by ukim              #+#    #+#             */
/*   Updated: 2021/05/03 18:36:32 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sort_env(t_env **sort_env, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	j = 0;
	while (j++ < size)
	{
		i = 0;
		while (++i < size)
		{
			if (ft_strcmp(sort_env[i - 1]->key, sort_env[i]->key) > 0)
			{
				tmp = sort_env[i - 1];
				sort_env[i - 1] = sort_env[i];
				sort_env[i] = tmp;
			}
		}
	}
}

void	print_export_sub(t_env **sort_env)
{
	int	i;
	int	j;

	i = 0;
	while (sort_env[i])
	{
		ft_putstr_fd("declear -x ", 1);
		ft_putstr_fd(sort_env[i]->key, 1);
		if (sort_env[i]->value)
		{
			write(1, "=\"", 2);
			j = 0;
			while (sort_env[i]->value[j])
			{
				if (sort_env[i]->value[j] == '\"')
					write(1, "\\", 1);
				ft_putchar_fd(sort_env[i]->value[j++], 1);
			}
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_export(void)
{
	t_env	*env;
	t_env	**sort_env;
	int		size;
	int		i;

	env = g_all.env_first;
	size = chk_arg_cnt_env();
	sort_env = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	i = -1;
	while (++i < size)
	{
		sort_env[i] = env;
		env = env->next;
	}
	sort_env[i] = 0;
	ft_sort_env(sort_env, size);
	print_export_sub(sort_env);
	free(sort_env);
}

void	put_env(char *str)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(key, str, i + 1);
	j = 0;
	if (str[i])
	{
		while (j++ < i + 1)
			str++;
		value = str;
	}
	else
		value = 0;
	lst_change_add_env(key, value);
	free(key);
}

int		exec_export(t_split_two *cmd)
{
	t_env	*env;
	int		i;

	env = g_all.env_first;
	i = 1;
	if (!cmd->cmd[1])
		print_export();
	while (cmd->cmd[i])
	{
		if (ft_isdigit(cmd->cmd[i][0]) || cmd->cmd[i][0] == '=')
			return (not_valid_idt(cmd, cmd->cmd[i], 1));
		put_env(cmd->cmd[i]);
		i++;
	}
	return (0);
}
