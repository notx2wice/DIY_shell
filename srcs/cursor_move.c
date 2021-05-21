/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/05/19 16:26:41 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_end()
{
	if(g_all.hist_now->data.top > 0)
	{	
		if (g_all.tc.curcol == 0)
		{
			tputs(tgoto(g_all.tc.cm, g_all.tc.col - 1, g_all.tc.currow - 1), 1, putchar_tc); // 커서를 커서 주소까지 이동
			tputs(g_all.tc.ce, 1, putchar_tc); // 커서 뒤에 있는 스트링을 지워줌
			g_all.hist_now->data.top--; // 현재 명령줄 문자열 위치를 수정해줌
		}
		else if (g_all.tc.curcol > 0)
		{
			g_all.hist_now->data.top--;
			tputs(tgoto(g_all.tc.cm, g_all.tc.curcol - 1, g_all.tc.currow), 1, putchar_tc);
			tputs(g_all.tc.ce, 1, putchar_tc);
		}
	}
	get_cursor_position(&g_all.tc.curcol, &g_all.tc.currow);
}

void	just_delete_end()
{
	if (g_all.tc.curcol == 0)
	{
		tputs(tgoto(g_all.tc.cm, g_all.tc.col - 1, g_all.tc.currow - 1), 1, putchar_tc);
		tputs(g_all.tc.ce, 1, putchar_tc);
	}
	else if (g_all.tc.curcol > 0)
	{
		tputs(tgoto(g_all.tc.cm, g_all.tc.curcol, g_all.tc.currow), 1, putchar_tc);
		tputs(g_all.tc.ce, 1, putchar_tc);
	}
}

void	clear_all_command_line()
{
	int i;

	i = -1;
	while (++i < g_all.hist_now->data.top)
	{
		just_delete_end();
	}
}
