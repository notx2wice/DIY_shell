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

	temp = make_hs_node(); // 새 히스토리를 만든다
	copy_hist(&g_all.hist_now, &temp); // 새 히스토리의 내용을 now 히스토리로 바꾼다.
	copy_hist(&g_all.thist_now, &g_all.hist_now); // now 히스토리의 내용을 thist now로 바꾼다
	g_all.hist_last->prev->next = temp; // 새로 만든 히스토리를 뒤에 추가한다
	temp->prev = g_all.hist_last->prev; // 새로 만든 히스토리의 전 포인터를 연결한다.
	// free_t_hist(&g_all.hist_last); // 
	g_all.hist_last = temp; //새로 만든 히스토리로 last를 초기화한다.
	g_all.hist_now = g_all.hist_last; // 현재 보고 있는 히스토리를 새로만든 히스토리로 수정한다.

}
