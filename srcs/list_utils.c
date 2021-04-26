/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:22:49 by ukim              #+#    #+#             */
/*   Updated: 2021/04/26 14:23:28 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void					init_s_two(t_split_two **two)
{
	(*two)->cmd_first = NULL;
	(*two)->next = NULL;
	(*two)->pipe_flag = 0;
	(*two)->redir_first = NULL;
	(*two)->redir_flag = 0;
	(*two)->termi_flag = 0;
}

void					add_back_two(t_split_two **first, t_split_two *added)
{
	t_split_two			*t_one;

	t_one = (*first);
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

void					init_redir_list(t_redir **r_list)
{
	(*r_list)->d_out_flag = 0;
	(*r_list)->in_flag = 0;
	(*r_list)->out_flag = 0;
	(*r_list)->next = NULL;
	(*r_list)->str = NULL;
	(*r_list)->str = (char*)malloc(sizeof(char) * BUFFS);
}

void					init_cmd_list(t_cmd_list **r_list)
{
	(*r_list)->disable = 0;
	(*r_list)->str  = NULL;
	(*r_list)->next = NULL;
}

void					add_back_cmd(t_cmd_list **first, t_cmd_list *added)
{
	t_cmd_list				*t_one;

	t_one = (*first);
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}