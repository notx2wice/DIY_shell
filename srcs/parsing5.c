/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:44:22 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 17:19:27 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			case_q_dq(t_split_two **lt, t_split_one **lc)
{
	t_cmd_list	*tmp_cmd;

	tmp_cmd = NULL;
	tmp_cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
	init_cmd_list(&tmp_cmd);
	tmp_cmd->str = ft_strdup((*lc)->str);
	add_back_cmd(&((*lt)->cmd_first), tmp_cmd);
}

void			case_normal(t_split_one **lc, t_split_two **lt)
{
	int			idx;
	t_cmd_list	*tmp_cmd;

	idx = 0;
	tmp_cmd = NULL;
	while ((*lc)->split_str[idx])
	{
		tmp_cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
		init_cmd_list(&tmp_cmd);
		tmp_cmd->str = ft_strdup((*lc)->split_str[idx]);
		add_back_cmd(&((*lt)->cmd_first), tmp_cmd);
		idx++;
	}
}

void			divide_with_tp(t_split_two **ft, t_split_two **lt, \
								t_split_one **lc)
{
	if ((*lc)->quote_flag || (*lc)->d_quote_flag)
		case_q_dq(lt, lc);
	else
		case_normal(lc, lt);
	if ((*lc)->redir_flag)
	{
		(*lt)->redir_flag = 1;
		(*lt)->redir_first = (*lc)->redir_first;
		(*lc)->redir_first = NULL;
	}
	if ((*lc)->pipe_flag || (*lc)->termi_flag)
	{
		if ((*lc)->pipe_flag)
			(*lt)->pipe_flag = 1;
		else
			(*lt)->termi_flag = 1;
		if ((*lc)->next != NULL)
		{
			(*lt) = (t_split_two*)malloc(sizeof(t_split_two));
			init_s_two(&(*lt));
			add_back_two(ft, (*lt));
		}
	}
}

void			make_two_by_one(t_split_one **fc, t_split_one **lc, \
								t_split_two **ft, t_split_two **lt)
{
	init_two(lt, ft);
	(*lc) = (*fc);
	while ((*lc))
	{
		if ((*lc)->disable)
		{
			(*lc) = (*lc)->next;
			continue ;
		}
		divide_with_tp(ft, lt, lc);
		(*lc) = (*lc)->next;
	}
}
