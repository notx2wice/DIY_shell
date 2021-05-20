/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:16:10 by ukim              #+#    #+#             */
/*   Updated: 2021/05/20 10:41:12 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		copy_hist(t_hist **ori, t_hist **cpy) // copy_process
{
	int		idx;

	idx = 0;
	while (idx <= (*ori)->data.top)
	{
		(*cpy)->data.tcarr[idx] = (*ori)->data.tcarr[idx];
		idx++;
	}
	(*cpy)->data.top = (*ori)->data.top;
}

void		copy_all_hist() //hist_copy
{
	t_hist	*hi;
	t_hist	*thi;
	t_hist	*temp;

	hi = g_all.hist_start;
	thi = g_all.thist_start;
	if (hi)
	{
		while (hi)
		{
			temp = make_hs_node();
			copy_hist(&hi, &temp);
			add_back_hs_node(&g_all.thist_start, temp);
			hi = hi->next;
		}
	}
}

void		free_t_hist(t_hist **freed_hist)
{
	t_hist	*temp;
	t_hist	*ttemp;

	if ((*freed_hist) == NULL)
		return ;
	temp = (*freed_hist);
	while (temp)
	{
		free(temp->data.tcarr);
		ttemp = temp;
		temp = temp->next;
		free(ttemp);
	}
	(*freed_hist) = NULL;
}

void		free_copy_thist()
{
	if (g_all.thist_start != NULL)
		free_t_hist(&g_all.thist_start);
	copy_all_hist();
}

void		link_thist_last_now()
{
	t_hist	*temp;

	temp = g_all.thist_start;
	while (temp->next)
		temp = temp->next;
	g_all.thist_now = temp;
	g_all.thist_last = temp;
}
