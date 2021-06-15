/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:11 by ukim              #+#    #+#             */
/*   Updated: 2021/06/15 16:25:42 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_isnum(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	else
		return (-1);
	return (1);
}

int			ft_iszero(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] == '-')
	{
		i++;
		flag = 1;
	}
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	if (flag == 1 && i == 1)
		return (0);
	return (1);
}

long long	ft_atoll(const char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (sign == 1 && num > (unsigned long long)LLONG_MAX)
		return (sign == 1 ? -1 : 0);
	if (sign != 1 && num > (unsigned long long)LLONG_MAX + 1)
		return (sign == 1 ? -1 : 0);
	return (sign * num);
}

int			chk_arg_digit(char *val)
{
	char			*str;
	long long		atoi_result;
	int				minus;

	str = val;
	if (ft_iszero(str) == 1)
		return (1);
	minus = 0;
	if (str[0] == '-')
		minus = 1;
	if (ft_isnum(&val[minus]) <= 0 || ft_strlen(val) > 19 + minus)
		return (0);
	atoi_result = ft_atoll(val);
	if (atoi_result > 0 || atoi_result < -1)
		return (1);
	if (ft_strcmp(str, "-1") == 0)
		return (1);
	return (0);
}

int			exec_exit(t_split_two *cmd)
{
	int cnt_arg;
	int	isdigit;

	cnt_arg = chk_arg_cnt(cmd);
	isdigit = chk_arg_digit(cmd->cmd[1]);
	if (cmd->cmd[1])
	{
		if (isdigit == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(num_arg_error(cmd, 255));
		}
		if (cnt_arg > 2)
		{
			ft_putstr_fd("exit\n", 1);
			return (too_many_arg_error(cmd, 1));
		}
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(cmd->cmd[1]));
	}
	ft_putstr_fd("exit\n", 1);
	exit(0);
	return (EXIT_SUCCESS);
}
