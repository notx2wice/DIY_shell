/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:48:14 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_end(void)
{
	if (g_all.hist_now->data.top > 0)
	{
		if (g_all.tc.curcol < 0 || g_all.tc.currow < 0)
			return ;
		if (g_all.tc.curcol == 0)
		{
			g_all.tc.currow--;
			g_all.tc.curcol = g_all.tc.col - 1;
			tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, \
			g_all.tc.currow), 1, putchar_tc);
			tputs(g_all.tc.ce, 1, putchar_tc);
			g_all.hist_now->data.top--;
		}
		else
		{
			g_all.tc.curcol--;
			tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, \
			g_all.tc.currow), 1, putchar_tc);
			tputs(g_all.tc.ce, 1, putchar_tc);
			g_all.hist_now->data.top--;
		}
	}
}

void	just_delete_end(void)
{
	if (g_all.tc.curcol == 0)
	{
		if (g_all.tc.currow != 0)
			g_all.tc.currow = g_all.tc.currow - 1;
		g_all.tc.curcol = g_all.tc.col - 1;
	}
	else if (g_all.tc.curcol > 0)
		g_all.tc.curcol = g_all.tc.curcol - 1;
}

void	move_curser(int mv_cnt)
{
	tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, \
	g_all.tc.currow), mv_cnt, putchar_tc);
	tputs(g_all.tc.ce, mv_cnt, putchar_tc);
}

void	clear_all_command_line(void)
{
	int i;

	i = -1;
	while (++i < g_all.hist_now->data.top)
		just_delete_end();
	if (i != 0)
		move_curser(i);
}
