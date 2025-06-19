NAME = contact_manager

SRC = main.c contact_manager.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

LIBFT = ./Libft/libft.a
PRINTF = ./Printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./Libft

$(PRINTF):
	make -C ./Printf

clean:
	rm -f $(OBJ)
	make -C ./Libft clean
	make -C ./Printf clean

fclean: clean
	rm -f $(NAME)
	make -C ./Libft fclean
	make -C ./Printf fclean

re: fclean all

.PHONY: all clean fclean re