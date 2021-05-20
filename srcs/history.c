/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/05/20 12:59:06 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					is_same_hist()
{
	int				idx;

	idx = 0;
	if (g_all.thist_now->data.top != g_all.hist_now->data.top)
		return (0);
	while (idx < g_all.hist_now->data.top)
	{
		if (g_all.hist_now->data.tcarr[idx] != g_all.thist_now->data.tcarr[idx])
			return (0);
		idx++;
	}
	return (1);
}

void				add_new_hist()
{
	t_hist			*temp;

	temp = make_hs_node();
	copy_hist(&g_all.hist_now, &temp);
	copy_hist(&g_all.thist_now, &g_all.hist_now);
	g_all.hist_last->prev->next = temp; //hist_start인데 왜 hist_last가 아닌것인가..
	temp->prev = g_all.hist_last->prev;
	free_t_hist(&g_all.hist_last);
	g_all.hist_last = temp;
	g_all.hist_now = g_all.hist_last;

}
