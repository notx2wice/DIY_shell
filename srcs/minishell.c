/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/06 16:23:11 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_addachar(char *str, char c)
{
	int		idx;
	int		len;
	char	*temp;

	idx = 0;
	len = ft_strlen(str);
	temp = (char*)malloc(sizeof(char) * (len + 2));
	while (idx < len)
	{
		temp[idx] = str[idx];
		idx++;
	}
	temp[idx] = c;
	if (str)
		free(str);
	return temp;
}

int		main(int ac, char **av, char **env)
{
	t_di_quote 	*t_q;
	char		*temp_l;
	
	temp_l = NULL;
	av = 0;
	env = 0;
	if (ac != 1)
	{
		printf("wrong argument\n");
		return (0);
	}
	
	char *str;
	str = "echo 123 ; ls |grep ; echo \"$HOME\"    ab\"$HOME\" \"\";";
	printf("%s\n", str);
	int idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\"')
		{
			
		}
		else if (str[idx] == '\'')
		{
			
		}
		else
			ft_addachar(temp_l, str[idx]);
		idx++;
	}
}

