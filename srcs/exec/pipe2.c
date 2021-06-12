/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:46:00 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:45:19 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_split_two	*exec_pipe(t_split_two *cmd)
{
	int		fds[count_pipes(cmd) * 2];
	int		cnt_pip;
	int		i;
	pid_t	pid[count_pipes(cmd) + 1];

	cnt_pip = count_pipes(cmd);
	i = -1;
	while (++i < cnt_pip)
		if (pipe(fds + (i * 2)) == -1)
			ft_error();
	i = -1;
	while (cmd && ++i < cnt_pip + 1)
	{
		if ((pid[i] = fork()) == -1)
			ft_error();
		g_all.child = 1;
		if (pid[i] == 0)
		{
			dup_fds(fds, i, cnt_pip);
			exec_default_pipe(cmd);
		}
		cmd = cmd->next;
	}
	wait_parent(fds, pid, cnt_pip);
	return (cmd);
}
