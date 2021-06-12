/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:14:15 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:48:29 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		num_arg_error(t_split_two *cmd, int err_num)
{
	ft_putstr_fd("mini ", 1);
	ft_putstr_fd(cmd->cmd[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(cmd->cmd[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	return (err_num);
}

int		too_many_arg_error(t_split_two *cmd, int err_num)
{
	ft_putstr_fd("mini ", 1);
	ft_putstr_fd(cmd->cmd[0], 1);
	ft_putstr_fd(": too many arguments\n", 1);
	return (err_num);
}

int		open_error(char *file)
{
	ft_putstr_fd("mini ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (-1);
}

int		no_home_error(t_split_two *cmd, int err_num)
{
	ft_putstr_fd("mini ", 1);
	ft_putstr_fd(cmd->cmd[0], 1);
	ft_putstr_fd(": HOME not set\n", 1);
	return (err_num);
}

void	syntax_error(void)
{
	ft_putstr_fd("\nmini>: syntax error with unexpected token", 1);
	g_all.exit_code = 258;
}
