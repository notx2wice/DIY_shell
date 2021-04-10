/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/10 22:35:39 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all	g_all;

void	init_term(void)
{
	char	*name;

	name = "xterm";
	tgetent(NULL, name);
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

void	sighandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (!g_all.minishell.forked)
			g_all.minishell.exit = 1;
		else
			g_all.minishell.exit = 130;
		write(1, "\n", 1);
		print_prompt();
		g_all.minishell.quit = 1;
		write(1, "cntl + c", ft_strlen("cntl + c"));
	}
	if (sig_num == SIGQUIT)
	{
		g_all.minishell.quit = 4;
		write(1, "cntl + \\", ft_strlen("cntl + \\"));
	}
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

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
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

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
}

int		main(int ac, char **av, char **env)
{
	int c;
	(void)ac;
	(void)av;
	(void)env;
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	init_term();
	print_prompt();
	while (read(0, &c, sizeof(c)))
	{	
		get_cursor_position(&g_all.tc.curcol, &g_all.tc.currow);
		if (c == EOF_KEY)
		{
			write(1, "\n", 1);
			print_prompt();
			g_all.minishell.quit = 4;
			write(1, "cntl + d", ft_strlen("cntl + d"));
		}
		else if (c == BACKSPACE)
			delete_end(g_all.tc.curcol, &g_all.tc.currow, g_all.tc.cm, g_all.tc.ce);
		else
		{
			g_all.tc.curcol++;
			write(0, &c, 1);
		}
		c = 0;
	}
}

