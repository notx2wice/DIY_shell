/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:40:56 by ukim              #+#    #+#             */
/*   Updated: 2021/04/12 14:28:37 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_term(void)
{
	char	*name;
	char	*env;

	env = getenv("TERM");
	if (env == NULL)
		env = "xterm";
	tgetent(NULL, env);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_all.tc.term);
	g_all.tc.term.c_lflag &= ~ICANON;
	g_all.tc.term.c_lflag &= ~ECHO;
	g_all.tc.term.c_cc[VMIN] = 1;
	g_all.tc.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_all.tc.term);
	g_all.tc.cm = tgetstr("cm", NULL);
	g_all.tc.ce = tgetstr("ce", NULL);
}

void	cursor_win(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_all.tc.col = w.ws_col;
	g_all.tc.row = w.ws_row;
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(1, "\033[6n", 4);  //report cursor location
	ret = read(1, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}
