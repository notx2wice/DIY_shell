/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:59:59 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 13:47:54 by ukim             ###   ########.fr       */
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

void		case_q_dllr(t_split_one **lc, char *cnv, int *idx)
{
	int		nbx;
	char	*nbr;

	if ((*lc)->split_str[idx[0]][idx[2] + 1] == '?' )
	{
		nbx = 0;
		nbr = NULL;
		nbr = ft_itoa(g_all.exit_code);
		if (nbr != NULL)
			while (nbr[nbx])
			{
				cnv[idx[1]++] = nbr[nbx];
				nbx++;
			}
		free(nbr);
		idx[2] += 2;
	}
	else
	{
		cnv[idx[1]++] = (*lc)->split_str[idx[0]][idx[2]++];
		cnv[idx[1]++] = (*lc)->split_str[idx[0]][idx[2]++];
	}
}

void		find_value_insert2(char *cnv, char *t_e_key, int *idx)
{
	int		start;
	t_env	*tmp_env;

	tmp_env = g_all.env_first;
	while (tmp_env)
	{
		if (ft_strcmp(t_e_key, tmp_env->key) == 0)
		{
			start = 0;
			while (tmp_env->value[start])
			{
				cnv[idx[1]++] = tmp_env->value[start];
				start++;
			}
			if (t_e_key != NULL)
			{
				free(t_e_key);
				t_e_key = NULL;
			}
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

void		change_dollar_roop(t_split_one **lc, int *idx, char *cnv, int *st)
{
	char	*t_e_key;

	while ((*lc)->split_str[idx[0]][idx[2]])
	{
		if ((*lc)->split_str[idx[0]][idx[2]] == '$')
			if ((*lc)->split_str[idx[0]][idx[2] + 1] == ' ' ||\
				(*lc)->split_str[idx[0]][idx[2] + 1] == '\0')
				cnv[idx[1]++] = (*lc)->split_str[idx[0]][idx[2]++];
			else if ((*lc)->split_str[idx[0]][idx[2] + 1] == '?' ||\
					(*lc)->split_str[idx[0]][idx[2] + 1] == '$')
				case_q_dllr(lc, cnv, idx);
			else
			{
				t_e_key = NULL;
				idx[2]++;
				make_st_end2(st, idx, lc);
				t_e_key = ft_substr((*lc)->split_str[idx[0]], st[0], st[1] - st[0]);
				find_value_insert2(cnv, t_e_key, idx);
			}
		else
			cnv[idx[1]++] = (*lc)->split_str[idx[0]][idx[2]++];
	}
}

void		it_is_in_split(t_split_one **fc, t_split_one **lc)
{
	int		idx[3];
	int		st[2];
	char	*cnv;

	idx[0] = 0;
	while ((*lc)->split_str[idx[0]])
	{
		chng_dllr_start_process2(&cnv, idx);
		change_dollar_roop(lc, idx, cnv, st);
		chng_dllr_end_process2(lc, cnv, idx);
	}
}

void		change_dollar_in_cmd(t_split_one **fc, t_split_one **lc)
{
	(*lc) = (*fc);
	while ((*lc))
	{
		if ((*lc)->d_quote_flag == 0 && (*lc)->quote_flag == 0)
		{
			(*lc)->split_str = ft_split((*lc)->str, ' ');
		}
		if ((*lc)->split_str != NULL)
		{
			it_is_in_split(fc, lc);
		}
		(*lc) = (*lc)->next;
	}
}
