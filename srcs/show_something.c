/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_something.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:55:23 by ukim              #+#    #+#             */
/*   Updated: 2021/04/09 18:44:43 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fd_printf(char *str)
{
	int idx;

	while(str[idx])
	{
		write(0, &str[idx], 1);
		idx++;
	}
}

void	print_prompt(void)
{
	write(1, "mini> ", 6);
}