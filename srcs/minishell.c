/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/13 17:09:44 by ukim             ###   ########.fr       */
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
	unsigned int	c;
	t_hist			*last;
	t_hist			*temp;
	(void)ac;
	(void)av;
	(void)env;
	
	last = NULL;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	init_all();
	g_all.hist_now = make_hs_node();
	add_back_hs_node(&g_all.hist_start, g_all.hist_now);
	last = g_all.hist_now;
	print_prompt();
	while (read(1, &c, sizeof(int)))
	{
		if (c == EOF_KEY) // cntl + d
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		else if (c == UP_ARROW)
		{
			
		}
		else if (c == DOWN_ARROW)
		{
			
		}
		else if (c == BACKSPACE)
		{
			get_cursor_position(&g_all.tc.curcol, &g_all.tc.currow);
			delete_end(&g_all.tc.curcol, &g_all.tc.currow, g_all.tc.cm, g_all.tc.ce);
		}
		else if (c == NEXT_LINE)
		{
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
