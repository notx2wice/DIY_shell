/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/15 12:12:19 by ukim             ###   ########.fr       */
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

int					main(int ac, char **av, char **env)
{
	int				c;
	(void)ac;
	(void)av;
	(void)env;
	
	t_hist			*temp;
	g_all.last = NULL;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	init_all();
	print_prompt();
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
			temp = g_all.hist_now;
			if (g_all.hist_now->prev)
			{
				g_all.hist_now = g_all.hist_now->prev;
				c = -1;
				while (++c < temp->data.top)
					just_delete_end();
				write(1, g_all.hist_now->data.tcarr, g_all.hist_now->data.top);
			}
			temp = NULL;
		}
		else if (c == DOWN_ARROW)
		{
			temp = g_all.hist_now;
			if (g_all.hist_now->next)
			{
				g_all.hist_now = g_all.hist_now->next;
				c = -1;
				while (++c < temp->data.top)
					just_delete_end();
				write(1, g_all.hist_now->data.tcarr, g_all.hist_now->data.top);
			}
			temp = NULL;
		}
		else if (c == BACKSPACE)
			delete_end(&g_all.tc.curcol, &g_all.tc.currow, g_all.tc.cm, g_all.tc.ce);
		else if (c == NEXT_LINE)
		{
			if (g_all.hist_now != g_all.last)//마지막 히스토리 면 저장 하고 새로 만들고 아니면 원래 마지막꺼랑 치환
			{
				temp = make_hs_node();
				copy_process(&g_all.hist_now, &temp);
				g_all.last->prev->next = temp;
				temp->prev = g_all.last->prev;
				free_t_hist(&g_all.last);
				g_all.last = temp;
			}
			write(1, "\n", 1);
			print_prompt();
		}
		else // maybe c should have short range for printable char
		{
			write(1, &c, 1);
			g_all.hist_now->data.tcarr[g_all.hist_now->data.top++] = (char)c;
		}
		c = 0;
	}
}
