NAME = minishell
SRC = minishell.c show_something.c
DIR = ./srcs/

SRCS = $(addprefix $(DIR), $(SRC))
LIBDIR = libft
LIBS = -L $(LIBDIR) -lft

HEADER = -I includes -I $(LIBDIR)
CC = gcc
CFLAG =   -lncurses #-Wall -Wextra -Werror

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