/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:43:19 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:49:37 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_hs_node(t_hist **node)
{
	(*node)->data.tcarr = (char*)malloc(sizeof(char) * BUFFS);
	(*node)->data.max_len = BUFFS;
	(*node)->data.top = 0;
	(*node)->next = NULL;
	(*node)->prev = NULL;
}

t_hist		*make_hs_node(void)
{
	t_hist	*temp;

	temp = (t_hist*)malloc(sizeof(t_hist));
	init_hs_node(&temp);
	return (temp);
}

void		add_back_hs_node(t_hist **head, t_hist *added)
{
	t_hist	*temp;

	temp = (*head);
	if ((*head) == NULL)
	{
		(*head) = added;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = added;
	added->prev = temp;
}

void		node_prev(t_hist **now)
{
	if ((*now)->prev == NULL)
	{
		return ;
	}
	(*now) = (*now)->prev;
}

void		node_next(t_hist **now)
{
	if ((*now)->next == NULL)
	{
		return ;
	}
	(*now) = (*now)->next;
}
