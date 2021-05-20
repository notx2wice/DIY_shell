/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:20:13 by ukim              #+#    #+#             */
/*   Updated: 2021/04/30 10:23:26 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			init_hists()
{
	g_all.hist_now = NULL;
	g_all.hist_start = NULL;
}

void			init_thists()
{
	g_all.thist_now = NULL;
	g_all.thist_start = NULL;
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
	init_hists();
	init_thists();
	print_prompt();
	copy_all_hist();
	link_thist_last_now();
}
