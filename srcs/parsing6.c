/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:58:38 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 16:33:38 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		case_in_redir(t_cmd_list **tmp_cmd, t_split_two **lt)
{
	t_redir *temp_redir;

	temp_redir = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(&temp_redir);
	if ((*tmp_cmd)->str[1])
	{
		(*tmp_cmd)->disable = 1;
		temp_redir->in_flag = 1;
		temp_redir->str = ft_substr((*tmp_cmd)->str, 1, ft_strlen((*tmp_cmd)->str) - 1);
	}
	else
	{
		if ((*tmp_cmd)->next == NULL)
			return (0);
		(*tmp_cmd)->disable = 1;
		temp_redir->in_flag = 1;
		(*tmp_cmd) = (*tmp_cmd)->next;
		if (ft_strncmp((*tmp_cmd)->str, "<", 1) == 0 || ft_strncmp((*tmp_cmd)->str, ">", 1) == 0)
			return (0);
		(*tmp_cmd)->disable = 1;
		temp_redir->str = ft_strdup((*tmp_cmd)->str);
	}
	add_back_redir(&(*lt)->redir_first, temp_redir);
	return (1);
}

int		case_out_redir(t_cmd_list **tmp_cmd, t_split_two **lt)
{
	t_redir *temp_redir;

	temp_redir = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(&temp_redir);
	if ((*tmp_cmd)->str[1])
	{
		(*tmp_cmd)->disable = 1;
		temp_redir->out_flag = 1;
		temp_redir->str = ft_substr((*tmp_cmd)->str, 1, ft_strlen((*tmp_cmd)->str) - 1);
	}
	else
	{
		if ((*tmp_cmd)->next == NULL)
			return (0);
		(*tmp_cmd)->disable = 1;
		temp_redir->out_flag = 1;
		(*tmp_cmd) = (*tmp_cmd)->next;
		if (ft_strncmp((*tmp_cmd)->str, "<", 1) == 0 || ft_strncmp((*tmp_cmd)->str, ">", 1) == 0)
			return (0);
		(*tmp_cmd)->disable = 1;
		temp_redir->str = ft_strdup((*tmp_cmd)->str);
	}
	add_back_redir(&(*lt)->redir_first, temp_redir);
	return (1);
}

int		case_d_out_redir(t_cmd_list **tmp_cmd, t_split_two **lt)
{
	t_redir *temp_redir;

	temp_redir = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(&temp_redir);
	if ((*tmp_cmd)->str[2])
	{
		(*tmp_cmd)->disable = 1;
		temp_redir->d_out_flag = 1;
		temp_redir->str = ft_substr((*tmp_cmd)->str, 2, ft_strlen((*tmp_cmd)->str) - 2);
	}
	else
	{
		if ((*tmp_cmd)->next == NULL)
			return (0);
		(*tmp_cmd)->disable = 1;
		temp_redir->d_out_flag = 1;
		(*tmp_cmd) = (*tmp_cmd)->next;
		if (ft_strncmp((*tmp_cmd)->str, "<", 1) == 0 || ft_strncmp((*tmp_cmd)->str, ">", 1) == 0)
			return (0);
		(*tmp_cmd)->disable = 1;
		temp_redir->str = ft_strdup((*tmp_cmd)->str);
	}
	add_back_redir(&(*lt)->redir_first, temp_redir);
	return (1);
}

int		when_two_have_redir(t_split_two **lt)
{
	t_redir *temp_redir;
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

int		make_redir_total(t_split_two **ft, t_split_two **lt)
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
