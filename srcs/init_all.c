/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:20:13 by ukim              #+#    #+#             */
/*   Updated: 2021/04/12 16:32:11 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_all()
{
	init_term();
	cursor_win();
	init_temp();
}

void		init_temp()
{
	g_all.tmp_input.max_len = 200;
	g_all.tmp_input.tcarr = (char*)malloc(sizeof(char) * 200);
	g_all.tmp_input.top = 0;
}