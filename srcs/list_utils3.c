/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:23:44 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 16:32:34 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				get_env(char *env[], t_env **env_first)
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
		init_env(&tmp_env);
		tmp_env->key = ft_substr(env[idx], 0, e_idx);
		if (len - e_idx > 0)
			tmp_env->value = ft_substr(env[idx], e_idx + 1, len - e_idx);
		add_back_env(env_first, tmp_env);
		idx++;
	}
}

void				add_back_one(t_split_one **first, t_split_one *added)
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
