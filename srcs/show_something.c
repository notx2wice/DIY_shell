/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_something.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:55:23 by ukim              #+#    #+#             */
/*   Updated: 2021/04/14 17:02:35 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(void)
{
	write(1, "mini> ", PROMPT_SIZE);
	g_all.hist_now = make_hs_node();
	add_back_hs_node(&g_all.hist_start, g_all.hist_now);
	g_all.last = g_all.hist_now;
}