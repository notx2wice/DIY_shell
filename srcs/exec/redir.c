/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:27:34 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:44:43 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		do_redir_in(t_redir *in)
{
	int		fd;
	t_redir	*tmp;

	tmp = in;
	while (tmp->next)
	{
		if ((fd = open(tmp->str, O_RDONLY)) == -1)
			return (open_error(tmp->str));
		if (close(fd) == -1)
			ft_error();
		tmp = tmp->next;
	}
	if ((in->fd = open(tmp->str, O_RDONLY)) == -1)
		return (open_error(tmp->str));
	in->fd_store = dup(0);
	dup2(in->fd, 0);
	return (0);
}

int		do_redir_out(t_redir *out)
{
	int		fd;
	t_redir	*tmp;

	tmp = out;
	while (tmp->next)
	{
		fd = open(tmp->str, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (close(fd) == -1)
			ft_error();
		tmp = tmp->next;
	}
	if (out->d_out_flag == 1)
		out->fd = open(tmp->str, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		out->fd = open(tmp->str, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	out->fd_store = dup(1);
	dup2(out->fd, 1);
	return (0);
}

int		change_redir(t_split_two *cmd)
{
	if (cmd->redir_in && (do_redir_in(cmd->redir_in) == -1))
		return (-1);
	if (cmd->redir_out)
		do_redir_out(cmd->redir_out);
	return (0);
}

void	getback_redir(t_split_two *cmd)
{
	if (cmd->redir_in)
	{
		dup2(cmd->redir_in->fd_store, 0);
		close(cmd->redir_in->fd_store);
	}
	if (cmd->redir_out)
	{
		dup2(cmd->redir_out->fd_store, 1);
		close(cmd->redir_out->fd_store);
	}
}
