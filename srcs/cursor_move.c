/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/06/14 15:11:15 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	move_curser(int mv_cnt)
{
	tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, \
	g_all.tc.currow), mv_cnt, putchar_tc);
	tputs(g_all.tc.ce, mv_cnt, putchar_tc);
}

void	delete_end(void)
{
	if (g_all.tc.curcol < 0 || g_all.tc.currow < 0)
		return ;
	if (g_all.tc.curcol == 0)
	{
		g_all.tc.currow--;
		g_all.tc.curcol = g_all.tc.col - 1;
	}
	else
		g_all.tc.curcol--;
	move_curser(1);
}

void	backspace_execute(void)
{
	if (g_all.hist_now->data.top > 0)
	{
		delete_end();
		g_all.hist_now->data.top--;
	}
}

void	clear_all_command_line(void)
{
	int i;

	i = -1;
	while (++i < g_all.hist_now->data.top)
		delete_end();
}
