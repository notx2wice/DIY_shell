/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:20:13 by ukim              #+#    #+#             */
/*   Updated: 2021/06/14 18:58:09 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			null_init_hist_and_thist(void)
{
	g_all.hist_now = NULL;
	g_all.hist_start = NULL;
	g_all.hist_last = NULL;
	g_all.thist_now = NULL;
	g_all.thist_start = NULL;
	g_all.thist_last = NULL;
}

void			re_init_thist(void)
{
	free_t_hist(&g_all.thist_start);
	copy_all_hist();
	link_thist_last_now();
	g_all.hist_now = g_all.hist_last;
}

void			init_all(char **env)
{
	get_env(env, &g_all.env_first);
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	g_all.exit_code = 0;
	g_all.child = 0;
	init_term();
	cursor_win();
	null_init_hist_and_thist();
	print_prompt();
}
