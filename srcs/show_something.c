/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_something.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 15:55:23 by ukim              #+#    #+#             */
/*   Updated: 2021/05/04 21:59:54 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(void)
{
	write(1, "mini> ", PROMPT_SIZE);
	g_all.hist_now = make_hs_node();
	add_back_hs_node(&g_all.hist_start, g_all.hist_now);
	g_all.hist_last = g_all.hist_now;
}

char	*get_env_value_by_key(char *key)
{
	t_env *tmp_env;

	tmp_env = g_all.env_first;
	while (tmp_env)
	{
		if (ft_strcmp(key, tmp_env->key) == 0)
		{
			return (ft_strdup(tmp_env->value));
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}