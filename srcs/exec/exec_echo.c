/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:06 by ukim              #+#    #+#             */
/*   Updated: 2021/05/03 18:30:45 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		chk_arg_cnt_env(void)
{
	t_env	*env;
	int		i;

	env = g_all.env_first;
	i = 0;
	while (env)
	{
		if (env->key)
			i++;
		env = env->next;
	}
	return (i);
}

int		chk_arg_cnt(t_split_two *cmd)
{
	int i;

	i = 0;
	if (cmd->cmd)
	{
		while (cmd->cmd[i])
			i++;
		return (i);
	}
	return (0);
}

void	print_val(t_split_two *cmd, int i, int cnt)
{
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (i < cnt - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

int		exec_echo(t_split_two *cmd)
{
	t_env	*env;
	int		cnt_arg;

	env = g_all.env_first;
	cnt_arg = chk_arg_cnt(cmd);
	if (cnt_arg > 2 && ft_strcmp(cmd->cmd[1], "-n") == 0)
		print_val(cmd, 2, cnt_arg);
	else
	{
		print_val(cmd, 1, cnt_arg);
		write(1, "\n", 1);
	}
	return (0);
}
