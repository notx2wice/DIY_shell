/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:08 by ukim              #+#    #+#             */
/*   Updated: 2021/04/27 11:02:29 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		exec_env()
{
	t_env	*env;

	env = g_all.env_first;
	while (env)
	{
		if (env->value)
		{
			ft_putstr(env->key);
			write(1, "=", 1);
			ft_putstr(env->value);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
