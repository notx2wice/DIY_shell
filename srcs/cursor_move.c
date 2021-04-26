/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/04/17 12:53:12 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col == 0 && g_all.hist_now->data.top > 0)
	{
		--(*row);
		g_all.tc.curcol = g_all.tc.col - 1;
		tputs(tgoto(cm, *col, *row), 1, putchar_tc); // 커서를 커서 주소까지 이동
		tputs(ce, 1, putchar_tc); // 커서 뒤에 있는 스트링을 지워줌
		g_all.hist_now->data.top--; // 현재 명령줄 문자열 위치를 수정해줌
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
	if (g_all.tc.curcol == 0) // 현재 커서의 x 위치가 0이면 / 줄이 넘어갔을경우만임
	{
		--(g_all.tc.currow); // 커서의 y 위치를 1 줄임 
		g_all.tc.curcol = g_all.tc.col - 1; // 터미널 가로의 전체에서 -1 빼줌
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