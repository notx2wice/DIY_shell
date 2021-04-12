/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:44:21 by ukim              #+#    #+#             */
/*   Updated: 2021/04/12 20:53:11 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col == 0 && g_all.hist_tmp->data.top > 0)
	{
		--(*row);
		(*col) = g_all.tc.col - 1;
		tputs(tgoto(cm, g_all.tc.col, *row), 1, putchar_tc);
		tputs(ce, 1, putchar_tc);
		g_all.hist_tmp->data.top--;
		tputs(tgoto(cm, *col, *row), 1, putchar_tc);
		return ;
	}
	else if (g_all.hist_tmp->data.top > 0)
	{
		g_all.hist_tmp->data.top--;
		--(*col);
	}
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
}