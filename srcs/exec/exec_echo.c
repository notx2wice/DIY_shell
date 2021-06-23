/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:06 by ukim              #+#    #+#             */
/*   Updated: 2021/06/23 16:43:16 by ukim             ###   ########.fr       */
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

int		until_not_n(t_split_two *cmd)
{
	t_split_two	*temp;
	int			idx;
	int			tdx;

	idx = 1;
	temp = cmd;
	while (temp->cmd[idx])
	{
		tdx = 0;
		if (temp->cmd[idx][tdx] == '-')
			tdx++;
		else
			return (idx);
		while (temp->cmd[idx][tdx])
		{
			if (temp->cmd[idx][tdx] != 'n')
				return (idx);
			tdx++;
		}
		idx++;
	}
	return (idx);
}

int		exec_echo(t_split_two *cmd)
{
	t_env	*env;
	int		cnt_arg;

	env = g_all.env_first;
	cnt_arg = chk_arg_cnt(cmd);
	if (until_not_n(cmd) > 1)
		print_val(cmd, until_not_n(cmd), cnt_arg);
	else
	{
		print_val(cmd, 1, cnt_arg);
		write(1, "\n", 1);
	}
	return (0);
}
