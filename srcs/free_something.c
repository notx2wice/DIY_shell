/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_something.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:38:59 by ukim              #+#    #+#             */
/*   Updated: 2021/06/13 15:50:36 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			free_2d_arr(char ***arr)
{
	int			idx;

	idx = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[idx])
	{
		free((*arr)[idx]);
		idx++;
	}
	free(*arr);
	*arr = NULL;
}

void			free_env(t_env **env_first)
{
	t_env		*temp;
	t_env		*free_temp;

	if (*env_first == NULL)
		return ;
	temp = *env_first;
	while (temp)
	{
		if (temp->key != NULL)
			free(temp->key);
		if (temp->value != NULL)
			free(temp->value);
		free_temp = temp;
		temp = temp->next;
		free(free_temp);
	}
	*env_first = NULL;
}

void			free_redir(t_redir **redir)
{
	t_redir		*temp_redir;
	t_redir		*free_temp;

	if (*redir == NULL)
		return ;
	temp_redir = *redir;
	while (temp_redir)
	{
		if (temp_redir->str != NULL)
			free(temp_redir->str);
		free_temp = temp_redir;
		temp_redir = temp_redir->next;
		free(free_temp);
	}
	*redir = NULL;
}

void			free_one(t_split_one **one)
{
	t_split_one *t_one;
	t_split_one *free_temp;

	if (*one == NULL)
		return ;
	t_one = *one;
	while (t_one)
	{
		if (t_one->redir_first != NULL)
			free_redir(&t_one->redir_first);
		if (t_one->str != NULL)
			free(t_one->str);
		if (t_one->split_str != NULL)
			free_2d_arr(&t_one->split_str);
		free_temp = t_one;
		t_one = t_one->next;
		free(free_temp);
	}
	*one = NULL;
}

void			free_cmd(t_cmd_list **cmd)
{
	t_cmd_list	*t_cmd;
	t_cmd_list	*free_temp;

	if (*cmd == NULL)
		return ;
	t_cmd = *cmd;
	while (t_cmd)
	{
		if (t_cmd->str != NULL)
			free(t_cmd->str);
		free_temp = t_cmd;
		t_cmd = t_cmd->next;
		free(free_temp);
	}
	*cmd = NULL;
}
