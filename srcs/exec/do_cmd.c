/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 10:52:53 by ukim              #+#    #+#             */
/*   Updated: 2021/04/30 12:54:52 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		empty_cmd_handler(t_split_two *cmd)
{
	if (cmd->redir_flag == TRUE)
	{
		if (change_redir(cmd) == -1)
			return (1);
		getback_redir(cmd);
		return (0);
	}
	else
	{
		syntax_error();
		return (258);
	}
}

void	exec_default(t_split_two *cmd)
{
	if (is_empty_cmd(cmd))
		g_all.exit_code = empty_cmd_handler(cmd);
	else if (is_built_in(cmd->cmd_first->str) == TRUE)
		g_all.exit_code = exec_builtin(cmd);
	else
		not_builtin_fork(cmd);
}

void	exec_default_pipe(t_split_two *cmd)
{
	if (is_empty_cmd(cmd))
		exit(empty_cmd_handler(cmd));
	else if (is_built_in(cmd->cmd_first->str) == 1)
		exit(exec_builtin(cmd));
	else
		exec_not_builtin(cmd);
}

int		is_built_in(char *command)
{
	if (ft_strcmp(command, "echo") == 0 ||
		ft_strcmp(command, "cd") == 0 ||
		ft_strcmp(command, "pwd") == 0 ||
		ft_strcmp(command, "export") == 0 ||
		ft_strcmp(command, "unset") == 0 ||
		ft_strcmp(command, "env") == 0 ||
		ft_strcmp(command, "exit") == 0)
		return (1);
	else
		return (0);
}

int		exec_builtin(t_split_two *cmd)
{
	int	ret;

	ret = 0;
	if (change_redir(cmd) == -1)
		return (1);
	if (ft_strcmp(cmd->cmd_first->str, "echo") == 0)
		ret = exec_echo(cmd);
	if (ft_strcmp(cmd->cmd_first->str, "cd") == 0)
		ret = exec_cd(cmd);
	if (ft_strcmp(cmd->cmd_first->str, "pwd") == 0)
		ret = exec_pwd(cmd);
	if (ft_strcmp(cmd->cmd_first->str, "export") == 0)
		ret = exec_export(cmd);
	if (ft_strcmp(cmd->cmd_first->str, "unset") == 0)
		ret = exec_unset(cmd);
	if (ft_strcmp(cmd->cmd_first->str, "env") == 0)
		ret = exec_env(cmd);
	if (ft_strcmp(cmd->cmd_first->str, "exit") == 0)
		ret = exec_exit(cmd);
	getback_redir(cmd);
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
