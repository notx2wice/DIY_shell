/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:11 by ukim              #+#    #+#             */
/*   Updated: 2021/05/03 13:12:47 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		chk_arg_digit(char *val)
{
	int i;

	i = 0;
	if (val)
	{
		while (val[i])
		{
			if (!ft_isdigit(val[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int		exec_exit(t_split_two *cmd)
{
	int cnt_arg;
	int	isdigit;

	cnt_arg = chk_arg_cnt(cmd);
	isdigit = chk_arg_digit(cmd->cmd[1]);
	if (cmd->cmd[1])
	{
		if (isdigit == 0)
		{
			ft_putstr("exit\n");
			exit(num_arg_error(cmd, 255));
		}
		if (cnt_arg > 2)
		{
			ft_putstr("exit\n");
			return (too_many_arg_error(cmd, 1));
		}
		ft_putstr("exit\n");
		exit(ft_atoi(cmd->cmd[1]));
	}
	ft_putstr("exit\n");
	exit(0);
	return (EXIT_SUCCESS);
}