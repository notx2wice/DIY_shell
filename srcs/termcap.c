/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:40:56 by ukim              #+#    #+#             */
/*   Updated: 2021/06/12 15:45:24 by seapark          ###   ########.fr       */
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

void	get_cursor_position(int *col, int *rows)
{
	char	buf[50];
	int		arr[3];

	write(1, "\033[6n", 5);
	arr[0] = read(1, buf, 49);
	buf[arr[0]] = '\0';
	arr[1] = 0;
	arr[2] = 0;
	while (buf[arr[2]++])
		if (buf[arr[2]] >= '0' && buf[arr[2]] <= '9')
		{
			if (arr[1] == 0)
			{
				*rows = ft_atoi(&buf[arr[2]]) - 1;
				arr[1] = 1;
			}
			else if (arr[1] == 2)
			{
				*col = ft_atoi(&buf[arr[2]]) - 1;
				return ;
			}
		}
		else if (buf[arr[2]] == ';')
			arr[1] = 2;
}
