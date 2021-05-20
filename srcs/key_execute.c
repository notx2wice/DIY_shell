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

void			up_arrow_execute()
{
	if (g_all.hist_now->prev)
	{
		clear_all_command_line();
		g_all.hist_now = g_all.hist_now->prev; // 바로 위 히스토리로 현재를 덮어씌움
		g_all.thist_now = g_all.thist_now->prev;
		write(1, g_all.hist_now->data.tcarr, *hist_now_data_top);
	}
}

void			down_arrow_excute()
{
	if (g_all.hist_now->next)
	{
		clear_all_command_line();
		g_all.hist_now = g_all.hist_now->next;
		g_all.thist_now = g_all.thist_now->next;
		write(1, g_all.hist_now->data.tcarr, *hist_now_data_top);
	}
}

void			next_line_execute()
{
	t_split_two		*now_cmd;
	int				*hist_now_data_top;

	hist_now_data_top = &(g_all.hist_now->data.top);
	if (g_all.hist_now != g_all.hist_last)
	{
		add_new_hist(); // 같으면 thist는 내비둠.
		if (*hist_now_data_top == 0) //명령줄에 아무것도 입력하지 않은 상태였다면 출력하기
		{
			re_init_thist();
			print_new_line_and_prompt();
			continue ;
		}
	}
	else if (*hist_now_data_top == 0)
	{
		print_new_line_and_prompt();
		continue ;
	}
	g_all.hist_now->data.tcarr[hist_now_data_top] = '\0';
	now_cmd = parsing(g_all.hist_now->data.tcarr); //현재명령 tcarr이 도대체 머임
	write(1, "\n", 1);
	if (now_cmd != NULL)
		exec_command(now_cmd);
	print_prompt();
	re_init_thist();
}

void			key_execute(int c)
{
	int				*hist_now_data_top;

	hist_now_data_top = &(g_all.hist_now->data.top);
	if (c == EOF_KEY) // cntl + d
	{
		if (*hist_now_data_top != 0)
			continue;
		write(1, "exit\n", 5);
		exit(g_all.exit_code); // 종료시 종료 인자 전달
	}
	else if (c == UP_ARROW)
		up_arrow_execute();
	else if (c == DOWN_ARROW)
		down_arrow_execute();
	else if (c == BACKSPACE) // 지우기 누를때
		delete_end(&g_all.tc.curcol, &g_all.tc.currow, g_all.tc.cm, g_all.tc.ce); // 지워지세요
	else if (c == NEXT_LINE) // \n 엔터 들어왔을때
		next_line_execute();
	else // maybe c should have short range for printable char
	{
		write(1, &c, 1);
		g_all.hist_now->data.tcarr[(*hist_now_data_top)++] = (char)c;
	}
}
