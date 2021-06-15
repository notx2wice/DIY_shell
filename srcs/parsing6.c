/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:58:38 by ukim              #+#    #+#             */
/*   Updated: 2021/06/15 15:42:32 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				case_in_redir(t_cmd_list **tmp_cmd, t_split_two **lt)
{
	t_redir		*tr;

	tr = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(&tr);
	free(tr->str);
	(*tmp_cmd)->disable = 1;
	tr->in_flag = 1;
	if ((*tmp_cmd)->str[1])
		tr->str = ft_substr((*tmp_cmd)->str, 1, ft_strlen((*tmp_cmd)->str) - 1);
	else
	{
		if ((*tmp_cmd)->next == NULL)
			return (free_return(tr));
		(*tmp_cmd) = (*tmp_cmd)->next;
		if (ft_strncmp((*tmp_cmd)->str, "<", 1) == 0 \
		|| ft_strncmp((*tmp_cmd)->str, ">", 1) == 0)
			return (free_return(tr));
		(*tmp_cmd)->disable = 1;
		tr->str = ft_strdup((*tmp_cmd)->str);
	}
	add_back_redir(&(*lt)->redir_first, tr);
	return (1);
}

int				case_out_redir(t_cmd_list **tmp_cmd, t_split_two **lt)
{
	t_redir		*tr;

	tr = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(&tr);
	free(tr->str);
	(*tmp_cmd)->disable = 1;
	tr->out_flag = 1;
	if ((*tmp_cmd)->str[1])
		tr->str = ft_substr((*tmp_cmd)->str, 1, ft_strlen((*tmp_cmd)->str) - 1);
	else
	{
		if ((*tmp_cmd)->next == NULL)
			return (free_return(tr));
		(*tmp_cmd) = (*tmp_cmd)->next;
		if (ft_strncmp((*tmp_cmd)->str, "<", 1) == 0 || \
		ft_strncmp((*tmp_cmd)->str, ">", 1) == 0)
			return (free_return(tr));
		(*tmp_cmd)->disable = 1;
		tr->str = ft_strdup((*tmp_cmd)->str);
	}
	add_back_redir(&(*lt)->redir_first, tr);
	return (1);
}

int				case_d_out_redir(t_cmd_list **tmp_cmd, t_split_two **lt)
{
	t_redir		*tr;

	tr = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(&tr);
	free(tr->str);
	(*tmp_cmd)->disable = 1;
	tr->d_out_flag = 1;
	if ((*tmp_cmd)->str[2])
		tr->str = ft_substr((*tmp_cmd)->str, 2, ft_strlen((*tmp_cmd)->str) - 2);
	else
	{
		if ((*tmp_cmd)->next == NULL)
			return (free_return(tr));
		(*tmp_cmd) = (*tmp_cmd)->next;
		if (ft_strncmp((*tmp_cmd)->str, "<", 1) == 0 || \
		ft_strncmp((*tmp_cmd)->str, ">", 1) == 0)
			return (free_return(tr));
		(*tmp_cmd)->disable = 1;
		tr->str = ft_strdup((*tmp_cmd)->str);
	}
	add_back_redir(&(*lt)->redir_first, tr);
	return (1);
}

int				when_two_have_redir(t_split_two **lt)
{
	t_cmd_list	*tmp_cmd;

	tmp_cmd = (*lt)->cmd_first;
	while (tmp_cmd)
	{
		if (ft_strncmp(tmp_cmd->str, ">>", 2) == 0)
		{
			if (case_d_out_redir(&tmp_cmd, lt) == 0)
				return (0);
		}
		else if (ft_strncmp(tmp_cmd->str, ">", 1) == 0)
		{
			if (case_out_redir(&tmp_cmd, lt) == 0)
				return (0);
		}
		else if (ft_strncmp(tmp_cmd->str, "<", 1) == 0)
		{
			if (case_in_redir(&tmp_cmd, lt) == 0)
				return (0);
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (1);
}

int				make_redir_total(t_split_two **ft, t_split_two **lt)
{
	(*lt) = (*ft);
	while ((*lt))
	{
		if ((*lt)->redir_flag)
		{
			if (when_two_have_redir(lt) == 0)
				return (0);
		}
		(*lt) = (*lt)->next;
	}
	return (1);
}
