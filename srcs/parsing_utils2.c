/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:08:19 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 18:09:45 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		make_st_end2(int *st, int *idx, t_split_one **lc)
{
	st[0] = idx[2];
	while ((*lc)->split_str[idx[0]][idx[2]] != '\0' && \
			(*lc)->split_str[idx[0]][idx[2]] != ' ' && \
			(*lc)->split_str[idx[0]][idx[2]] != '$')
	{
		idx[2]++;
	}
	st[1] = idx[2];
}

void		chng_dllr_start_process2(char **cnv, int *idx)
{
	idx[1] = 0;
	idx[2] = 0;
	(*cnv) = (char*)malloc(sizeof(char) * BUFFS);
}

void		chng_dllr_end_process2(t_split_one **lc, char *cnv, int *idx)
{
	cnv[idx[1]] = '\0';
	free((*lc)->split_str[idx[0]]);
	(*lc)->split_str[idx[0]] = NULL;
	(*lc)->split_str[idx[0]] = cnv;
	idx[0]++;
}
