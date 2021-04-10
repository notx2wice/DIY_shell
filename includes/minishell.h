/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:43:30 by ukim              #+#    #+#             */
/*   Updated: 2021/04/10 22:19:10 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <string.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
#include "../libft/libft.h"

# define EOF_KEY 4
# define BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699

typedef struct		s_minishell
{
	char			*name;
	char			*curdir;
	long int		exit;
	char			*line;
	int				quit;
	int				quit2;
	int				count;
	int				scope_p;
	int				forked;
	char			*exit_str;
	char			**env_array;
	char			**bin;
}					t_minishell;

typedef struct		s_hist
{
	char			*str;
	struct s_hist	*prev;
	struct s_hist	*next;
	char			*line;
}					t_hist;

typedef struct		s_termcap
{
	struct termios	term;
	struct termios	term_backup;
	char			*backup_cmd;
	char			*copy_cmd;
	int				start_row;
	int				start_col;
	int				col;
	int				row;
	int				plen;
	int				cur_pos;
	int				currow;
	int				curcol;
	int				lenlen;
	int				rowoffset;
	int				mod_offset;
	int				endcol;
	int				endrow;
	char			*cm;
	char			*ce;
	char			*dl;
	long			backspace;
}					t_termcap;

typedef struct		s_all
{
	t_hist			hist;
	t_hist			cursor_hist;
	t_termcap		tc;
	t_minishell		minishell;
}					t_all;

extern t_all		g_all;

void		print_prompt(void);

#endif