/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 14:18:26 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all	g_all;

void	sighandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (g_all.child == 1)
		{
			g_all.exit_code = 130;
			write(1, "^C\n", 3);
		}
		else
		{
			g_all.exit_code = 1;
			g_all.hist_now = g_all.hist_last;
			g_all.hist_last->data.top = 0;
			write(1, "\nmini> ", 7);
		}
		return ;
	}
	if (sig_num == SIGQUIT)
	{
		if (g_all.child == 1)
		{
			g_all.exit_code = 131;
			write(1, "Quit: 3\n", 8);
		}
		return ;
	}
}

void	print_new_line_and_prompt(void)
{
	write(1, "\n", 1);
	write(1, "mini> ", PROMPT_SIZE);
}

int		main(int ac, char **av, char *env[])
{
	int		c;

	init_all(env);
	c = 0;
	while (read(0, &c, sizeof(int)))
	{
		get_cursor_position(&g_all.tc.curcol, &g_all.tc.currow);
		key_execute(c);
		c = 0;
	}
	
}
