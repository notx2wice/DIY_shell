/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:23:44 by ukim              #+#    #+#             */
/*   Updated: 2021/05/19 16:27:04 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void					add_back_env(t_env **first, t_env *added)
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

void					add_back_redir(t_redir **first, t_redir *added)
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

void					init_s_one(t_split_one **one)
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
	(*one)->split_str = NULL; // *** 포인터는 초기화가 자동으로 안됨 !!!
	(*one)->str = (char*)malloc(sizeof(char) * BUFFS);
}

int					get_char_index(char *arr, char c)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if(arr[i] == c)
			break;
		i++;
	}
	return i;
}

void		init_env(t_env *s_env)
{
	s_env = (t_env*)malloc(sizeof(s_env));
	s_env->key = NULL;
	s_env->value = NULL;
	s_env->next = NULL;
}

void			get_env(char *env[], t_env **env_first)
{
	int			idx;
	int			e_idx;
	int			len;
	t_env		*tmp_env;

	idx = 0;
	while (env[idx])
	{
		e_idx = get_char_index(env[idx], '=');
		len = ft_strlen(env[idx]);
		if (len == 0)
		{
			idx++;
			continue ;
		}
		init_env(tmp_env);
		tmp_env->key = ft_substr(env[idx], 0, e_idx);
		if (len - e_idx > 0)
			tmp_env->value = ft_substr(env[idx], e_idx + 1, len - e_idx);
		add_back_env(env_first, tmp_env);
		idx++;
	}
}

void					add_back_one(t_split_one **first, t_split_one *added)
{
	t_split_one			*t_one;

	t_one = (*first);
	if ((*first) == NULL)
	{
		(*first) = added;
		return ;
	}
	while (t_one->next)
		t_one = t_one->next;
	t_one->next = added;
}
