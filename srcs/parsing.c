/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:29:54 by ukim              #+#    #+#             */
/*   Updated: 2021/06/15 15:44:34 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				add_cmd_txt(t_split_one **s_cmd, char *str_cmd)
{
	int i;

	i = 0;
	while (str_cmd[i] != '\'' && str_cmd[i])
	{
		(*s_cmd)->str[(*s_cmd)->top++] = str_cmd[i];
		i++;
	}
	return (i);
}

void			init_cmd(t_split_one **last_cmd, t_split_one **first_cmd)
{
	(*last_cmd) = (t_split_one*)malloc(sizeof(t_split_one));
	init_s_one(last_cmd);
	add_back_one(first_cmd, (*last_cmd));
}

void			init_two(t_split_two **last_two, t_split_two **first_two)
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

t_split_two		*parsing(char *str_ori)
{
	t_split_one	*first_cmd;
	t_split_one	*last_cmd;
	t_split_two	*first_two;
	t_split_two	*last_two;

	first_cmd = NULL;
	first_two = NULL;
	init_cmd(&last_cmd, &first_cmd);
	if (divide_with_ptqd(&first_cmd, &last_cmd, str_ori) == 0)
		return_free_one_two(&first_cmd, &first_two);
	make_strend_null(&first_cmd, &last_cmd);
	change_dollar_in_dq(&first_cmd, &last_cmd);
	change_dollar_in_cmd(&first_cmd, &last_cmd);
	make_two_by_one(&first_cmd, &last_cmd, &first_two, &last_two);
	if (make_redir_total(&first_two, &last_two) == 0)
		return_free_one_two(&first_cmd, &first_two);
	make_list_2d_arr(&first_two, &last_two);
	make_in_out_r_lst(&first_two, &last_two, &first_cmd);
	return (first_two);
}
