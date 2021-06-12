/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:46:00 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:35:19 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_pipes(t_split_two *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd)
	{
		if (cmd->pipe_flag == 1)
			cnt++;
		else
			break ;
		cmd = cmd->next;
	}
	return (cnt);
}

void	close_fds(int fds[], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
		close(fds[i++]);
}

void	dup_fds(int fds[], int i, int pipe_count)
{
	if (i < pipe_count)
		dup2(fds[i * 2 + 1], 1);
	if (i > 0)
		dup2(fds[(i - 1) * 2], 0);
	close_fds(fds, pipe_count);
}

void	wait_parent(int fds[], pid_t pid[], int cnt)
{
	int		status;
	int		i;

	close_fds(fds, cnt);
	i = -1;
	while (++i < cnt + 1)
		waitpid(pid[i], &status, 0);
	g_all.child = 0;
	if (WIFEXITED(status))
		g_all.exit_code = WEXITSTATUS(status);
}

void	exec_default_pipe(t_split_two *cmd)
{
	if (is_empty_cmd(cmd))
		exit(empty_cmd_handler(cmd));
	else if (is_built_in(cmd->cmd[0]) == 1)
		exit(exec_builtin(cmd));
	else
		exec_not_builtin(cmd);
}
