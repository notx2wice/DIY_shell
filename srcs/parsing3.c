/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 20:54:26 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 13:25:28 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		case_question(char *cnv, int *idx)
{
	int		nbx;
	char	*nbr;

	nbx = 0;
	nbr = NULL;
	nbr = ft_itoa(g_all.exit_code);
	if (nbr != NULL)
		while (nbr[nbx])
		{
			cnv[idx[1]++] = nbr[nbx];
			nbx++;
		}
	idx[0] = idx[0] + 2;
	free(nbr);
}

void		make_start_end(int *idx, int *start, int *end, t_split_one **lc)
{
	(*start) = (*idx);
	while ((*lc)->str[(*idx)] != '\0' && (*lc)->str[(*idx)] != ' ' &&\
			(*lc)->str[(*idx)] != '$')
		(*idx)++;
	(*end) = (*idx);
}

void		find_value_insert(char *cnv, char *t_e_key, int *idx)
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

void		chng_dllr_end_process(t_split_one **lc, char *cnv, int *idx)
{
	cnv[idx[1]] = '\0';
	free((*lc)->str);
	(*lc)->str = NULL;
	(*lc)->str = cnv;
}

void		chng_dllr_start_process(char **cnv, int *idx)
{
	idx[0] = 0;
	idx[1] = 0;
	(*cnv) = (char*)malloc(sizeof(char) * BUFFS);
}

void		for_norm_shit(char *cnv, t_split_one **lc, int *idx)
{
	cnv[idx[1]++] = (*lc)->str[idx[0]++];
	cnv[idx[1]++] = (*lc)->str[idx[0]++];
}

void		it_is_in_dq(t_split_one **fc, t_split_one **lc)
{
	int		idx[2];
	int		start[2];
	char	*cnv;
	char	*t_e_key;

	chng_dllr_start_process(&cnv, idx);
	while ((*lc)->str[idx[0]])
		if ((*lc)->str[idx[0]] == '$')
			if ((*lc)->str[idx[0] + 1] == ' ' || (*lc)->str[idx[0] + 1] == '\0')
				cnv[idx[1]++] = (*lc)->str[idx[0]++];
			else if ((*lc)->str[idx[0] + 1] == '?')
				case_question(cnv, idx);
			else if ((*lc)->str[idx[0] + 1] == '$')
				for_norm_shit(cnv, lc, idx);
			else
			{
				t_e_key = NULL;
				idx[0]++;
				make_start_end(&(idx[0]), &start[0], &start[1], lc);
				t_e_key = ft_substr((*lc)->str, start[0], start[1] - start[0]);
				find_value_insert(cnv, t_e_key, idx);
			}
		else
			cnv[idx[1]++] = (*lc)->str[idx[0]++];
	chng_dllr_end_process(lc, cnv, idx);
}

void		change_dollar_in_dq(t_split_one **fc, t_split_one **lc)
{
	while ((*lc))
	{
		if ((*lc)->d_quote_flag)
		{
			it_is_in_dq(fc, lc);
		}
		(*lc) = (*lc)->next;
	}
}
