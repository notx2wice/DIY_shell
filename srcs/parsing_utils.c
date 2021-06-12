/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:04:50 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 18:10:01 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				count_cmd(t_cmd_list *cmd)
{
	int			idx;

	idx = 0;
	while (cmd)
	{
		if (cmd->disable == 0)
			idx++;
		cmd = cmd->next;
	}
	return (idx);
}

void			make_start_end(int *idx, int *start, int *end, t_split_one **lc)
{
	(*start) = (*idx);
	while ((*lc)->str[(*idx)] != '\0' && (*lc)->str[(*idx)] != ' ' &&\
			(*lc)->str[(*idx)] != '$')
		(*idx)++;
	(*end) = (*idx);
}

void			chng_dllr_end_process(t_split_one **lc, char *cnv, int *idx)
{
	cnv[idx[1]] = '\0';
	free((*lc)->str);
	(*lc)->str = NULL;
	(*lc)->str = cnv;
}

void			chng_dllr_start_process(char **cnv, int *idx)
{
	idx[0] = 0;
	idx[1] = 0;
	(*cnv) = (char*)malloc(sizeof(char) * BUFFS);
}
