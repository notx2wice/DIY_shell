/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 14:17:50 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_end()
{
	if(g_all.hist_now->data.top > 0)
	{
		if (g_all.tc.curcol < 0 || g_all.tc.currow < 0)
			return ;
		if (g_all.tc.curcol == 0)
		{
			g_all.tc.currow--;
			g_all.tc.curcol = g_all.tc.col - 1;
			tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
			tputs(g_all.tc.ce, 1, putchar_tc); // 커서 뒤에 있는 스트링을 지워줌
			g_all.hist_now->data.top--; // 현재 명령줄 문자열 위치를 수정해줌
		}
		else
		{
			g_all.tc.curcol--;
			tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
			tputs(g_all.tc.ce, 1, putchar_tc);
			g_all.hist_now->data.top--;
		}
	}
}

void	just_delete_end()
{
	if (g_all.tc.currow < 0)
	{
		printf("\nerror : currow가 음수입니다.\n");
		return ;
	}
	if (g_all.tc.curcol < 0)
	{
		printf("\nerror : curcol 음수입니다.\n");
		return ;
	}
	if (g_all.tc.curcol == 0)
	{
		if (g_all.tc.currow != 0)
		{
			g_all.tc.currow = g_all.tc.currow - 1;
		}
		else
		{
			printf("\ncurcol가 0이에요\n");
		}
		g_all.tc.curcol = g_all.tc.col - 1;
		// tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
		// tputs(g_all.tc.ce, 1, putchar_tc);
	}
	else if (g_all.tc.curcol > 0)
	{
		// get_cursor_position(&g_all.tc.curcol, &g_all.tc.currow);
		g_all.tc.curcol = g_all.tc.curcol - 1;
		// tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
		// tputs(g_all.tc.ce, 1, putchar_tc);
	}
}

void move_curser(int mv_cnt)
{
	tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), mv_cnt, putchar_tc);
	tputs(g_all.tc.ce, mv_cnt, putchar_tc);
	// printf("\n%d %d\n", g_all.tc.curcol, g_all.tc.currow);
}

void	clear_all_command_line()
{
	int i;
	i = -1;
	while (++i < g_all.hist_now->data.top)
	{
		just_delete_end();
	}
	if (i != 0)
		move_curser(i);
}
