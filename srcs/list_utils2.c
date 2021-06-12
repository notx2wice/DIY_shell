/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:23:44 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:32:22 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				add_back_env(t_env **first, t_env *added)
{
	t_env				*t_one;

	if (added == NULL)
		return ;
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	t_one = (*first);
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

void				add_back_redir(t_redir **first, t_redir *added)
{
	t_redir				*t_one;

	if (added == NULL)
		return ;
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	t_one = (*first);
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}

void				init_s_one(t_split_one **one)
{
	(*one)->d_quote_flag = 0;
	(*one)->pipe_flag = 0;
	(*one)->quote_flag = 0;
	(*one)->termi_flag = 0;
	(*one)->disable = 0;
	(*one)->top = 0;
	(*one)->next = NULL;
	(*one)->redir_first = NULL;
	(*one)->str = NULL;
	(*one)->split_str = NULL;
	(*one)->str = (char*)malloc(sizeof(char) * BUFFS);
}

int					get_char_index(char *arr, char c)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == c)
			break ;
		i++;
	}
	return (i);
}

void				init_env(t_env **s_env)
{
	(*s_env) = (t_env*)malloc(sizeof(t_env));
	(*s_env)->key = NULL;
	(*s_env)->value = NULL;
	(*s_env)->next = NULL;
}
