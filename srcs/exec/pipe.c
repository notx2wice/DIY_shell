/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:46:00 by ukim              #+#    #+#             */
/*   Updated: 2021/06/15 14:25:16 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		close_fds(int fds[], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
		close(fds[i++]);
}

void		dup_fds(int fds[], int i, int pipe_count)
{
	if (i < pipe_count)
		dup2(fds[i * 2 + 1], 1);
	if (i > 0)
		dup2(fds[(i - 1) * 2], 0);
	close_fds(fds, pipe_count);
}

void		wait_parent(int fds[], pid_t pid[], int cnt)
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

void		exec_default_pipe(t_split_two *cmd)
{
	if (is_empty_cmd(cmd))
		exit(empty_cmd_handler(cmd));
	else if (is_built_in(cmd->cmd[0]) == 1)
		exit(exec_builtin(cmd));
	else
		exec_not_builtin(cmd);
}

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
