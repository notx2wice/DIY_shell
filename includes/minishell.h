/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:43:30 by ukim              #+#    #+#             */
/*   Updated: 2021/05/21 15:29:44 by ukim             ###   ########.fr       */
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
# define NEXT_LINE 10
# define BUFFS 4000
# define PROMPT_SIZE 6
# define EXIT_SUCCESS 0

typedef struct			s_redir
{
	int					out_flag;
	int					in_flag;
	int					d_out_flag;
	int					fd;
	int					fd_store;
	char				*str;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_split_one
{
	int					redir_flag;
	int					pipe_flag;
	int					quote_flag;
	int					d_quote_flag;
	int					termi_flag;
	int					top;
	int					disable;
	char				*str;
	char				**split_str;
	struct s_redir		*redir_first;
	struct s_split_one	*next;
}						t_split_one;

typedef struct			s_cmd_list
{
	int					disable;
	char				*str;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct			s_split_two
{
	int					redir_flag;
	int					pipe_flag;
	int					termi_flag;
	t_cmd_list			*cmd_first;
	char				**cmd;
	struct s_redir		*redir_first;
	struct s_redir		*redir_in;
	struct s_redir		*redir_out;
	struct s_split_two	*next;
	int					ispath;
}						t_split_two;

typedef struct			s_tmp_input
{
	char				*tcarr;
	int					max_len;
	int					top;
}						t_tmp_input;

typedef struct			s_hist
{
	t_tmp_input			data;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

typedef struct			s_termcap
{
	struct termios		term;
	int					col;//max term col
	int					row;//max term row
	int					prompt_row;//the latest prompt row
	int					currow;
	int					curcol;
	char				*cm;
	char				*ce;
}						t_termcap;

typedef struct			s_all
{
	t_hist				*hist_start;
	t_hist				*hist_now;
	t_hist				*thist_start;
	t_hist				*thist_now;
	t_hist				*hist_last;
	t_hist				*thist_last;
	t_hist				*temp;
	t_termcap			tc;
	t_env				*env_first;
	int					child;
	int					exit_code;
}						t_all;

extern t_all			g_all;

void		print_prompt(void);
int			putchar_tc(int tc);
int			nbr_length(int n);
void		cursor_win(void);
void		get_cursor_position(int *col, int *rows);
void		delete_end(int *col, int *row, char *cm, char *ce);
void		just_delete_end();

//init
void		init_all(void);
void		init_term(void);
void		init_s_two(t_split_two **two);
void		init_redir_list(t_redir **r_list);
void		init_s_one(t_split_one **one);
void		init_cmd_list(t_cmd_list **r_list);

//list_util
void		add_back_one(t_split_one **first, t_split_one *added);
void		add_back_two(t_split_two **first, t_split_two *added);
void		add_back_cmd(t_cmd_list **first, t_cmd_list *added);
void		add_back_env(t_env **first, t_env *added);
void		add_back_redir(t_redir **first, t_redir *added);
t_split_one	*find_last_one(t_split_one *first);

//double list
void		init_hs_node(t_hist **node);
t_hist		*make_hs_node();
void		add_back_hs_node(t_hist **head, t_hist *added);
void		node_prev(t_hist **now);
void		node_next(t_hist **now);
void		init_hists();
void		init_thists();
//free things
void		free_t_hist(t_hist **freed_hist); //free normal t_hist
void		free_copy_thist();
void		free_2d_arr(char ***arr);
void		free_env(t_env **env_first);
void		free_redir(t_redir **redir);
void		free_one(t_split_one **one);
void		free_cmd(t_cmd_list **cmd);
void		free_two(t_split_two **two);

//histoty
void		copy_all_hist();
void		copy_hist(t_hist **ori, t_hist **cpy);
void		link_thist_last_now();
int			is_same_hist();
 //env
void		get_env(char *env[], t_env **env_first);
//parse
t_split_two	*parsing(char *str_ori);
char		*get_env_value_by_key(char *key);
int			divide_with_ptqd(t_split_one **first_cmd, t_split_one **last_cmd, char *cmd);
void		change_dollar_in_dq(t_split_one **first_cmd, t_split_one **last_cmd);
void		find_value_insert(char *cnv, char *t_e_key, int *idx);
void		make_start_end(int *idx, int *start, int *end, t_split_one **lc);
void		change_dollar_in_cmd(t_split_one **fc, t_split_one **lc);
void		make_two_by_one(t_split_one **fc, t_split_one **lc, t_split_two **ft, t_split_two **lt);

//exec
int			get_cmd_list_length(t_split_two *cmd);
void		lst_change_add_env(char *key, char *val);
int			chk_arg_cnt_env(void);
int			chk_arg_cnt(t_split_two *cmd);
int			exec_cd(t_split_two *cmd);
int			exec_echo(t_split_two *cmd);
int			exec_env();
int			exec_exit(t_split_two *cmd);
int			exec_export(t_split_two *cmd);
int			exec_pwd();
int			exec_unset(t_split_two *cmd);
void		exec_command(t_split_two *now_cmd);
void		exec_not_builtin(t_split_two *cmd);
t_split_two	*exec_pipe(t_split_two *cmd);
int			is_built_in(char *cmd);
int			exec_builtin(t_split_two *cmd);
void		exec_default_pipe(t_split_two *cmd);
int			change_redir(t_split_two *cmd);
void		getback_redir(t_split_two *cmd);

//error
void	ft_error(void);
int		not_valid_idt(t_split_two *cmd, char *arg, int err_num);
int		no_file_error(t_split_two *cmd, int err_num);
int		no_command_error(t_split_two *cmd, int err_num);
int		no_home_error(t_split_two *cmd, int err_num);
int		open_error(char *file);
int		too_many_arg_error(t_split_two *cmd, int err_num);
int		num_arg_error(t_split_two *cmd, int err_num);
int		not_valid_idt(t_split_two *cmd, char *arg, int err_num);
void	syntax_error(void);
int		is_empty_cmd(t_split_two *cmd);
int		empty_cmd_handler(t_split_two *cmd);

//추가한  
int		get_char_index(char *arr, char c);
void	init_env(t_env **s_env);
void	clear_all_command_line();
int		add_cmd_txt(t_split_one **s_cmd, char *str_cmd);
void	init_cmd(t_split_one **last_cmd, t_split_one **first_cmd);
void	init_two(t_split_two **last_two, t_split_two **first_two);

#endif
