/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 20:20:00 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 17:16:33 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	meet_pipe_termi(t_split_one **fc, t_split_one **lc, char c)
{
	if (c == '|')
	{
		(*lc)->pipe_flag = 1;
		init_cmd(lc, fc);
	}
	else
	{
		(*lc)->termi_flag = 1;
		init_cmd(lc, fc);
	}
}

int		meet_d_q(t_split_one **fc, t_split_one **lc, int *idx, char *cmd)
{
	init_cmd(lc, fc);
	(*idx)++;
	(*lc)->d_quote_flag = 1;
	while (cmd[(*idx)] != '\"' && cmd[(*idx)])
	{
		(*lc)->str[(*lc)->top++] = cmd[(*idx)];
		(*idx)++;
	}
	if (!cmd[(*idx)])
		return (0);
	init_cmd(lc, fc);
	return (1);
}

int		meet_q(t_split_one **fc, t_split_one **lc, int *idx, char *cmd)
{
	init_cmd(lc, fc);
	(*idx)++;
	(*lc)->quote_flag = 1;
	(*idx) += add_cmd_txt(&(*lc), &cmd[(*idx)]);
	if (!cmd[(*idx)])
		return (0);
	init_cmd(lc, fc);
	return (1);
}

int		meet_redir(t_split_one **lc, int *idx, char *cmd)
{
	if (cmd[(*idx) + 1] != 0)
	{
		(*lc)->redir_flag = 1;
		if (cmd[(*idx)] == '>' && cmd[(*idx) + 1] == '>')
		{
			(*lc)->str[(*lc)->top++] = ' ';
			(*lc)->str[(*lc)->top++] = cmd[(*idx)];
			(*lc)->str[(*lc)->top++] = cmd[(*idx)++];
		}
		else if (cmd[(*idx) + 1] == '>' || cmd[(*idx) + 1] == '<')
			return (0);
		else
		{
			(*lc)->str[(*lc)->top++] = ' ';
			(*lc)->str[(*lc)->top++] = cmd[(*idx)];
		}
	}
	else
	{
		(*lc)->redir_flag = 1;
		(*lc)->str[(*lc)->top++] = ' ';
		(*lc)->str[(*lc)->top++] = cmd[(*idx)];
	}
	return (1);
}

int		divide_with_ptqd(t_split_one **fc, t_split_one **lc, char *cmd)
{
	int		idx;

	idx = -1;
	while (cmd[++idx])
		if (cmd[idx] == '|' || cmd[idx] == ';')
			meet_pipe_termi(fc, lc, cmd[idx]);
		else if (cmd[idx] == '\'')
		{
			if ((meet_q(fc, lc, &idx, cmd) == 0))
				return (0);
		}
		else if (cmd[idx] == '\"')
		{
			if ((meet_d_q(fc, lc, &idx, cmd) == 0))
				return (0);
		}
		else if (cmd[idx] == '<' || cmd[idx] == '>')
		{
			if ((meet_redir(lc, &idx, cmd) == 0))
				return (0);
		}
		else
			(*lc)->str[(*lc)->top++] = cmd[idx];
	(*lc)->termi_flag = 1;
	return (1);
}
