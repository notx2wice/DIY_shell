/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:08:38 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:49:50 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		no_command_error(t_split_two *cmd, int err_num)
{
	ft_putstr_fd("mini> ", 1);
	ft_putstr_fd(cmd->cmd[0], 1);
	ft_putstr_fd(": command not found\n", 1);
	return (err_num);
}

int		no_file_error(t_split_two *cmd, int err_num)
{
	ft_putstr_fd("mini> ", 1);
	ft_putstr_fd(cmd->cmd[0], 1);
	if (cmd->cmd[1])
	{
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(cmd->cmd[1], 1);
	}
	ft_putstr_fd(": No such file or directory\n", 1);
	return (err_num);
}

int		not_valid_idt(t_split_two *cmd, char *arg, int err_num)
{
	ft_putstr_fd("mini> ", 1);
	ft_putstr_fd(cmd->cmd[0], 1);
	ft_putstr_fd(": '", 1);
	ft_putstr_fd(arg, 1);
	ft_putstr_fd("': not a valid identifierd\n", 1);
	return (err_num);
}

void	ft_error(void)
{
	ft_putstr_fd("mini> error: ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
	exit(EXIT_FAILURE);
}
