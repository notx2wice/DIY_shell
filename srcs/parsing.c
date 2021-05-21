/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:29:54 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 16:31:39 by ukim             ###   ########.fr       */
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

int			add_cmd_txt(t_split_one **s_cmd, char *str_cmd)
{
	int i;

	i = 0;
	while (str_cmd[i] != '\'' && str_cmd[i])
	{
		(*s_cmd)->str[(*s_cmd)->top++] = str_cmd[i];
		i++;
	}
	return i;
}

void	init_cmd(t_split_one **last_cmd, t_split_one **first_cmd)
{
	(*last_cmd) = (t_split_one*)malloc(sizeof(t_split_one));
	init_s_one(last_cmd);
	add_back_one(first_cmd, (*last_cmd));
}

void	init_two(t_split_two **last_two, t_split_two **first_two)
{
	(*last_two) = (t_split_two*)malloc(sizeof(t_split_two));
	init_s_two(last_two);
	add_back_two(first_two, (*last_two));
}

void			make_strend_null(t_split_one **fc, t_split_one **lc)
{
	(*lc) = (*fc);
	while ((*lc))
	{
		(*lc)->str[(*lc)->top] = '\0';
		(*lc) = (*lc)->next;
	}
}

t_split_two		*parsing(char *str_ori) //스플릿 원과 투 구조체가 있는데 투로 리턴한다..
{
	int			idx;
	int			tidx;
	char		*cnv_d_quoat;
	char		*temp_env_key;
	char		*temp_env_value;
	int			start;
	int			end;
	t_split_one	*first_cmd;
	t_split_one *last_cmd;
	t_split_two *first_two;
	t_split_two *last_two;
	t_cmd_list	*tmp_cmd;
	t_redir		*temp_redir;
	t_env		*tmp_env;
	first_cmd = NULL;
	last_cmd = NULL;
	first_two = NULL;
	temp_redir = NULL;
	init_cmd(&last_cmd, &first_cmd);
	if (divide_with_ptqd(&first_cmd, &last_cmd, str_ori) == 0)
	{
		syntax_error();
		return (NULL);
	}
	make_strend_null(&first_cmd, &last_cmd);
	change_dollar_in_dq(&first_cmd, &last_cmd);
	change_dollar_in_cmd(&first_cmd, &last_cmd);
	make_two_by_one(&first_cmd, &last_cmd, &first_two, &last_two);
	if (make_redir_total(&first_two, &last_two) == 0)
	{
		syntax_error();
		return (NULL);
	}
	free_one(&first_cmd);
	int cmd_cnt;
	idx = 0;
	last_two = first_two;
	while (last_two)
	{
		tmp_cmd = last_two->cmd_first;
		cmd_cnt = count_cmd(tmp_cmd);
		last_two->cmd = (char**)malloc(sizeof(char*) * (cmd_cnt + 1));
		last_two->cmd[cmd_cnt] = NULL;
		cmd_cnt = 0;
		idx = 0;
		while (tmp_cmd)
		{
			if (tmp_cmd->disable == 0)
			{
				last_two->cmd[idx] = ft_strdup(tmp_cmd->str);
				idx++;
			}
			tmp_cmd = tmp_cmd->next;
		}
		last_two = last_two->next;
	}

	t_redir *new_redir = NULL;
	last_two = first_two;
	while (last_two)
	{
		if (last_two->redir_flag == 1)
		{
			temp_redir = last_two->redir_first;
			while (temp_redir)
			{
				if (temp_redir->in_flag == 1)
				{
					new_redir = (t_redir*)malloc(sizeof(t_redir));
					init_redir_list(&new_redir);
					new_redir->in_flag = 1;
					new_redir->str = temp_redir->str;
					temp_redir->str = NULL;
					add_back_redir(&last_two->redir_in, new_redir);
				}
				else if(temp_redir->out_flag == 1 || temp_redir->d_out_flag == 1)
				{
					new_redir = (t_redir*)malloc(sizeof(t_redir));
					init_redir_list(&new_redir);
					if (temp_redir->out_flag == 1)
						new_redir->out_flag = 1;
					else
						new_redir->d_out_flag = 1;
					new_redir->str = temp_redir->str;
					temp_redir->str = NULL;
					add_back_redir(&last_two->redir_out, new_redir);
				}
				temp_redir = temp_redir->next;
			}
		}
		last_two = last_two->next;
	}
	return (first_two);
}
