/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/04/15 12:08:30 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col == 0 && g_all.hist_now->data.top > 0)
	{
		--(*row);
		g_all.tc.curcol = g_all.tc.col - 1;
		tputs(tgoto(cm, *col, *row), 1, putchar_tc);
		tputs(ce, 1, putchar_tc);
		g_all.hist_now->data.top--;
		return ;
	}
	else if (g_all.hist_now->data.top > 0)
	{
		g_all.hist_now->data.top--;
		--g_all.tc.curcol;
		tputs(tgoto(cm, *col, *row), 1, putchar_tc);
		tputs(ce, 1, putchar_tc);
	}
}

void	just_delete_end()
{
	if (g_all.tc.curcol == 0)
	{
		--(g_all.tc.currow);
		g_all.tc.curcol = g_all.tc.col - 1;
		tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
		tputs(g_all.tc.ce, 1, putchar_tc);
		return ;
	}
	else
	{
		--g_all.tc.curcol;
		tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
		tputs(g_all.tc.ce, 1, putchar_tc);
	}
}