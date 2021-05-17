/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:52:53 by ukim              #+#    #+#             */
/*   Updated: 2021/05/03 19:10:24 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

int		exec_builtin(t_split_two *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ret = exec_echo(cmd);
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ret = exec_cd(cmd);
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ret = exec_pwd(cmd);
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ret = exec_export(cmd);
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		ret = exec_unset(cmd);
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ret = exec_env(cmd);
	if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ret = exec_exit(cmd);
	//getback_redir(cmd);
	return (ret);
}

void	not_builtin_fork(t_split_two *cmd)
{
	pid_t	pid;
	int		status;

	g_all.child = 1;
	if ((pid = fork()) == -1)
		ft_error();
	if (pid == 0)
		exec_not_builtin(cmd);
	else if (pid > 0)
	{
		wait(&status);
		g_all.child = 0;
		if (WIFEXITED(status))
			g_all.exit_code = WEXITSTATUS(status);
	}
}

void	exec_default(t_split_two *cmd)
{
	if (is_built_in(cmd->cmd[0]) == TRUE)
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
