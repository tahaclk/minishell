NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LRFLAGS = -lreadline

LIBFT = ./libft/libft.a

SRCS = add_set_merge.c create_args.c enviroment2.c exec.c fd.c handlers.c is_functions2.c main.c quotes.c redirection.c syntax.c \
builtins.c dollar.c enviroment.c exec_shell.c finding.c heredoc.c is_functions3.c print.c quote_size.c re_malloc.c tilde.c \
controls.c edit_list.c enviroment_utils.c exit.c free.c init.c is_functions.c quotes2.c quotes_utils.c set_keyval.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LRFLAGS) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft
	make bonus -C ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re