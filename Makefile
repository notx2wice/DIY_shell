NAME = minishell

SRC = minishell.c show_something.c termcap.c cursor_move.c \
		init_all.c double_list_util.c utils.c list_utils.c \
		list_utils2.c parsing.c free_something.c error.c \
		error2.c parsing2.c parsing3.c parsing4.c

EXEC = do_cmd.c do_not_built_in_cmd.c exec_cd.c exec_echo.c \
		exec_env.c exec_exit.c exec_export.c exec_pwd.c \
		exec_unset.c pipe.c redir.c

DIR = ./srcs/
EXECDIR = ./srcs/exec/

SRCS = $(addprefix $(DIR), $(SRC)) $(addprefix $(EXECDIR), $(EXEC))
LIBDIR = libft
LIBS = -L $(LIBDIR) -lft

HEADER = -I includes -I $(LIBDIR)
CC = gcc
CFLAG = -lncurses -fsanitize=address#-Wall -Wextra -Werror

OBJ = $(SRCS:.c=.o)

%.o: %.c
		$(CC) $(CFLAG) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIBDIR)
		@$(CC) $(CFLAG) $(OBJ) $(HEADER) $(LIBS) -o $@

clean:
		@/bin/rm -rf $(OBJ)
		@make -C $(LIBDIR) clean


fclean:
		@/bin/rm -rf $(OBJ)
		@/bin/rm -f $(NAME)
		@make -C $(LIBDIR) fclean

re: fclean all