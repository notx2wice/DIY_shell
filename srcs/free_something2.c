/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_something2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:38:59 by ukim              #+#    #+#             */
/*   Updated: 2021/06/15 15:44:56 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			free_two(t_split_two **two)
{
	t_split_two	*t_two;
	t_split_two	*free_temp;

	if (*two == NULL)
		return ;
	t_two = *two;
	while (t_two)
	{
		if (t_two->redir_first != NULL)
			free_redir(&t_two->redir_first);
		if (t_two->cmd_first != NULL)
			free_cmd(&t_two->cmd_first);
		if (t_two->redir_in != NULL)
			free_redir(&t_two->redir_in);
		if (t_two->redir_out != NULL)
			free_redir(&t_two->redir_out);
		if (t_two->cmd != NULL)
			free_2d_arr(&t_two->cmd);
		free_temp = t_two;
		t_two = t_two->next;
		free(free_temp);
	}
	*two = NULL;
}

int				return_free_one_two(t_split_one **one, t_split_two **two)
{
	syntax_error();
	free_one(one);
	free_two(two);
	return (0);
}

int				free_return(t_redir *redir)
{
	free(redir);
	return (0);
}
