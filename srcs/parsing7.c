/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:26:53 by ukim              #+#    #+#             */
/*   Updated: 2021/06/15 14:12:03 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			make_list_2d_arr(t_split_two **ft, t_split_two **lt)
{
	int			idx;
	int			cmd_cnt;
	t_cmd_list	*tmp_cmd;

	idx = 0;
	(*lt) = (*ft);
	while ((*lt))
	{
		tmp_cmd = (*lt)->cmd_first;
		cmd_cnt = count_cmd(tmp_cmd);
		(*lt)->cmd = (char**)malloc(sizeof(char*) * (cmd_cnt + 1));
		(*lt)->cmd[cmd_cnt] = NULL;
		cmd_cnt = 0;
		idx = 0;
		while (tmp_cmd)
		{
			if (tmp_cmd->disable == 0)
			{
				(*lt)->cmd[idx] = ft_strdup(tmp_cmd->str);
				idx++;
			}
			tmp_cmd = tmp_cmd->next;
		}
		(*lt) = (*lt)->next;
	}
}

void			when_in_flag(t_redir **n_re, t_split_two **lt, t_redir *tmp_re)
{
	(*n_re) = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(n_re);
	(*n_re)->in_flag = 1;
	free((*n_re)->str);
	(*n_re)->str = tmp_re->str;
	tmp_re->str = NULL;
	add_back_redir(&(*lt)->redir_in, (*n_re));
}

void			when_out_flag(t_redir **n_re, t_split_two **lt, t_redir *tmp_re)
{
	(*n_re) = (t_redir*)malloc(sizeof(t_redir));
	init_redir_list(n_re);
	if (tmp_re->out_flag == 1)
		(*n_re)->out_flag = 1;
	else
		(*n_re)->d_out_flag = 1;
	free((*n_re)->str);
	(*n_re)->str = tmp_re->str;
	tmp_re->str = NULL;
	add_back_redir(&(*lt)->redir_out, *n_re);
}

void			make_in_out_r_lst(t_split_two **ft, t_split_two **lt,\
				t_split_one **ff)
{
	t_redir		*n_re;
	t_redir		*tmp_re;

	(*lt) = (*ft);
	while ((*lt))
	{
		if ((*lt)->redir_flag == 1)
		{
			tmp_re = (*lt)->redir_first;
			while (tmp_re)
			{
				if (tmp_re->in_flag == 1)
					when_in_flag(&n_re, lt, tmp_re);
				else if (tmp_re->out_flag == 1 || tmp_re->d_out_flag == 1)
				{
					when_out_flag(&n_re, lt, tmp_re);
				}
				tmp_re = tmp_re->next;
			}
		}
		(*lt) = (*lt)->next;
	}
	free_one(ff);
}
