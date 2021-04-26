/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/17 13:05:04 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all	g_all;

void				sighandler(int sig_num)
{
	if (sig_num == SIGINT) // cntl + c
	{	//이때 문자열 입력을 받는 버퍼를 날리고 새로 할당 한후 커런트로 이어 줘야함.
		
	}
	if (sig_num == SIGQUIT) // cntl + back slash
	{
		
	}
}

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

int					main(int ac, char **av, char **env)
{
	int				c;
	(void)ac;
	(void)av;
	(void)env;
	
	t_hist			*temp;
	t_hist			*ttemp;
	g_all.last = NULL;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	init_all();
	print_prompt();
	free_t_hist(&g_all.thist_start);
	hist_copy();
	link_thist_last_now();
	while (read(1, &c, sizeof(int)))
	{
		get_cursor_position(&g_all.tc.curcol, &g_all.tc.currow);
		if (c == EOF_KEY) // cntl + d
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		else if (c == UP_ARROW)
		{
			temp = g_all.hist_now; // 현재 명령줄 저장
			ttemp = g_all.thist_now;
			if (g_all.hist_now->prev)
			{
				g_all.hist_now = g_all.hist_now->prev; // 바로 위 히스토리로 현재를 덮어씌움
				g_all.thist_now = g_all.thist_now->prev;
				c = -1;
				while (++c < temp->data.top) // 저장해놓은 현재 명령줄 크기 만큼
					just_delete_end(); // 현재 터미널의 문자를 다 지움
				// 내가 명령줄에서 뭘 쳤던간에 위를 누르면 명령줄에 쳤던걸 다 지움
				write(1, g_all.hist_now->data.tcarr, g_all.hist_now->data.top);
			}
			temp = NULL;
			ttemp = NULL;
		}
		else if (c == DOWN_ARROW)
		{
			temp = g_all.hist_now;
			ttemp = g_all.thist_now;
			if (g_all.hist_now->next)
			{
				g_all.hist_now = g_all.hist_now->next;
				g_all.thist_now = g_all.thist_now->next;
				c = -1;
				while (++c < temp->data.top)
					just_delete_end();
				write(1, g_all.hist_now->data.tcarr, g_all.hist_now->data.top);
			}
			temp = NULL;
			ttemp = NULL;
		}
		else if (c == BACKSPACE) // 지우기 누를때
			delete_end(&g_all.tc.curcol, &g_all.tc.currow, g_all.tc.cm, g_all.tc.ce); // 지워지세요
		else if (c == NEXT_LINE) // \n 엔터 들어왔을때
		{
			if (g_all.hist_now != g_all.last)//마지막 히스토리 면 저장 하고 새로 만들고 아니면 원래 마지막꺼랑 치환
			{
				if (is_same_hist())
				{
					temp = make_hs_node();
					copy_process(&g_all.hist_now, &temp);
					g_all.last->prev->next = temp;
					temp->prev = g_all.last->prev;
					free_t_hist(&g_all.last);
					g_all.last = temp;
				}
				else
				{
					temp = make_hs_node();
					copy_process(&g_all.hist_now, &temp);
					copy_process(&g_all.thist_now, &g_all.hist_now);
					g_all.last->prev->next = temp;
					temp->prev = g_all.last->prev;
					free_t_hist(&g_all.last);
					g_all.last = temp;
				}
			}
			else
			{
				if (g_all.hist_now->data.top == 0)
				{
					write(1, "\n", 1);
					//do_cmd;
					write(1, "mini> ", PROMPT_SIZE);
					continue ;
				}
			}
			write(1, "\n", 1);
			//do_cmd;
			print_prompt();
			//copy to thist;
			free_t_hist(&g_all.thist_start);
			hist_copy();
			link_thist_last_now();
		}
		else // maybe c should have short range for printable char
		{
			write(1, &c, 1);
			g_all.hist_now->data.tcarr[g_all.hist_now->data.top++] = (char)c;
		}
		c = 0;
	}
}
