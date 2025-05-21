CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
