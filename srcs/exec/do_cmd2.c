/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:52:53 by ukim              #+#    #+#             */
/*   Updated: 2021/06/13 17:00:53 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_default(t_split_two *cmd)
{
	if (is_empty_cmd(cmd))
		g_all.exit_code = empty_cmd_handler(cmd);
	else if (is_built_in(cmd->cmd[0]) == TRUE)
		g_all.exit_code = exec_builtin(cmd);
	else
		not_builtin_fork(cmd);
}

void	exec_command(t_split_two *now_cmd)
{
	t_split_two	*cmd;

	cmd = now_cmd;
	while (cmd)
	{
		if (cmd->pipe_flag == 1)
		{
			cmd = exec_pipe(cmd);
			continue;
		}
		exec_default(cmd);
		cmd = cmd->next;
	}
}
