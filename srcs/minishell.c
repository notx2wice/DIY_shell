/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/12 18:17:28 by ukim             ###   ########.fr       */
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
	(void)ac;
	(void)av;
	(void)env;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	init_all();
	print_prompt();
	while (read(1, &c, sizeof(int)))
	{
		if (c == EOF_KEY) // cntl + d
		{
		
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
		else
		{
			write(1, &c, 1);
			g_all.tmp_input.tcarr[g_all.tmp_input.top] = (char)c;
			g_all.tmp_input.top++;
		}
		c = 0;
	}
}
