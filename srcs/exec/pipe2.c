/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:46:00 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 17:06:36 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_pipes(t_split_two *cmd)
{
	int	cnt;

	cnt = 0;
	while (cmd)
	{
		if (cmd->pipe_flag == 1)
			cnt++;
		else
			break ;
		cmd = cmd->next;
	}
	return (cnt);
}
