/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/06/23 16:05:43 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			up_arrow_execute(void)
{
	int				*hist_now_data_top;

	if (g_all.hist_now->prev)
	{
		clear_all_command_line();
		g_all.hist_now = g_all.hist_now->prev;
		g_all.thist_now = g_all.thist_now->prev;
		hist_now_data_top = &(g_all.hist_now->data.top);
		write(1, g_all.hist_now->data.tcarr, *hist_now_data_top);
	}
}

void			down_arrow_execute(void)
{
	int				*hist_now_data_top;

	if (g_all.hist_now->next)
	{
		clear_all_command_line();
		g_all.hist_now = g_all.hist_now->next;
		g_all.thist_now = g_all.thist_now->next;
		hist_now_data_top = &(g_all.hist_now->data.top);
		write(1, g_all.hist_now->data.tcarr, *hist_now_data_top);
	}
}

int				empty_hist_now(void)
{
	int				*hist_now_data_top;

	hist_now_data_top = &(g_all.hist_now->data.top);
	if (*hist_now_data_top == 0)
	{
		print_new_line_and_prompt();
		return (1);
	}
	return (0);
}

void			next_line_execute(void)
{
	t_split_two		*now_cmd;

	if (g_all.hist_now != g_all.hist_last)
	{
		add_new_hist();
		if (empty_hist_now())
		{
			re_init_thist();
			return ;
		}
	}
	else if (empty_hist_now())
		return ;
	g_all.hist_now->data.tcarr[g_all.hist_now->data.top] = '\0';
	now_cmd = parsing(g_all.hist_now->data.tcarr);
	write(1, "\n", 1);
	set_term_flag(1);
	if (now_cmd != NULL)
		exec_command(now_cmd);
	free_two(&now_cmd);
	print_prompt();
	set_term_flag(0);
	re_init_thist();
}

void			key_execute(int c)
{
	int				*hist_now_data_top;

	hist_now_data_top = &(g_all.hist_now->data.top);
	if (c == EOF_KEY)
	{
		if (*hist_now_data_top != 0)
			return ;
		write(1, "exit\n", 5);
		exit(g_all.exit_code);
	}
	else if (c == UP_ARROW)
		up_arrow_execute();
	else if (c == DOWN_ARROW)
		down_arrow_execute();
	else if (c == BACKSPACE)
		backspace_execute();
	else if (c == NEXT_LINE)
		next_line_execute();
	else if (c < 256)
	{
		write(1, &c, 1);
		g_all.hist_now->data.tcarr[*hist_now_data_top] = c;
		g_all.hist_now->data.top++;
		g_all.tc.curcol++;
	}
}
