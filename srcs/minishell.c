/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:33:36 by ukim              #+#    #+#             */
/*   Updated: 2021/04/06 14:34:45 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int ac, char **av, char **env)
{
	av = 0;
	env = 0;
	if (ac != 1)
	{
		printf("wrong argument\n");
		return (0);
	}
	//ascii_art();
	/* 터미널 옵션 제어 */
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	int c = 0;
	printf("\033[6n");
	while (read(0, &c, sizeof(c)) > 0)
	{
		
		printf("keycode: %d\n", c);
				c = 0; // flush buffer
	}
}

