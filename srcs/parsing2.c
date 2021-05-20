/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 20:20:00 by ukim              #+#    #+#             */
/*   Updated: 2021/05/20 23:10:28 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	meet_pipe_termi(t_split_one **first_cmd, t_split_one **last_cmd, int flag)
{
	if (flag == 0)
	{
		(*last_cmd)->pipe_flag = 1;
		init_cmd(last_cmd, first_cmd);
	}
	else
	{
		(*last_cmd)->termi_flag = 1; //왜 termi?
		init_cmd(last_cmd, first_cmd);
	}
}

int		meet_d_q(t_split_one **first_cmd, t_split_one **last_cmd, int *idx, char *cmd)
{
	init_cmd(last_cmd, first_cmd);
	(*idx)++;
	(*last_cmd)->d_quote_flag = 1;
	while (cmd[(*idx)] != '\"' && cmd[(*idx)])
	{
		(*last_cmd)->str[(*last_cmd)->top++] = cmd[(*idx)];
		(*idx)++;
	}
	if (!cmd[(*idx)])
		return (0);
	init_cmd(last_cmd, first_cmd);
	return (1);
}

int		meet_q(t_split_one **first_cmd, t_split_one **last_cmd, int *idx, char *cmd)
{
	init_cmd(last_cmd, first_cmd);
	(*idx)++;
	(*last_cmd)->quote_flag = 1; //왜 전에 만든건 빈채로 내비두고 한개 더만든거에 플래그를 수정?
	idx += add_cmd_txt(&(*last_cmd), &cmd[(*idx)]);
	if (!cmd[(*idx)])// 명령어가 널문자라면? -> ' 하나만 있고 끝인 경우
		return (0);
	init_cmd(last_cmd, first_cmd);
	return (1);
}

int		meet_redir(t_split_one **first_cmd, t_split_one **last_cmd, int *idx, char *cmd)
{
	if (cmd[(*idx) + 1] != 0)
	{
		(*last_cmd)->redir_flag = 1;
		if (cmd[(*idx)] == '>' && cmd[(*idx) + 1] == '>')
		{
			(*last_cmd)->str[(*last_cmd)->top++] = ' ';
			(*last_cmd)->str[(*last_cmd)->top++] = cmd[(*idx)];
			(*last_cmd)->str[(*last_cmd)->top++] = cmd[(*idx)++];
		}
		else if (cmd[(*idx) + 1] == '>' || cmd[(*idx) + 1] == '<')
		{
			if (cmd[(*idx)] == cmd[(*idx) + 1])
				return 0;
		}
		else
		{
			(*last_cmd)->str[(*last_cmd)->top++] = ' ';
			(*last_cmd)->str[(*last_cmd)->top++] = cmd[(*idx)];
		}
	}
	else
	{
		(*last_cmd)->redir_flag = 1;
		(*last_cmd)->str[(*last_cmd)->top++] = ' ';
		(*last_cmd)->str[(*last_cmd)->top++] = cmd[(*idx)];
	}
	return (1);
}

int		divide_with_ptqd(t_split_one **first_cmd, t_split_one **last_cmd, char *cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx]) //명령어 파싱 시작
	{
		if (cmd[idx] == '|') //파이프일때 pipe
			meet_pipe_termi(first_cmd, last_cmd, 0);
		else if (cmd[idx] == ';') // semicolon
			meet_pipe_termi(first_cmd, last_cmd, 1);
		else if (cmd[idx] == '\'')//quote 변수로 만들어서 관리하면 좋을듯.
		{
			if ((meet_q(first_cmd, last_cmd, &idx, cmd) == 0))
				return 0;
		}
		else if (cmd[idx] == '\"')
		{
			if ((meet_d_q(first_cmd, last_cmd, &idx, cmd) == 0))
				return 0;
		}
		else if (cmd[idx] == '<' || cmd[idx] == '>')
		{
			if ((meet_redir(first_cmd, last_cmd, &idx, cmd) == 0))
				return 0;
		}
		else
			(*last_cmd)->str[(*last_cmd)->top++] = cmd[idx];
		idx++;
	}
	(*last_cmd)->termi_flag = 1;
	return (1);
}