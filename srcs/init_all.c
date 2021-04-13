/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:20:13 by ukim              #+#    #+#             */
/*   Updated: 2021/04/13 12:34:52 by ukim             ###   ########.fr       */
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

void			init_all()
{
	init_term();
	cursor_win();
	init_hists();
	init_thists();
}
