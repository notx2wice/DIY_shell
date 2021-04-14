/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:16:10 by ukim              #+#    #+#             */
/*   Updated: 2021/04/14 16:40:36 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		copy_process(t_hist **ori, t_hist **cpy)
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

void		hist_copy()
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
			copy_process(&hi, &temp);
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
	hist_copy();
}