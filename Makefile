CC=cc
LIBFT_NAME=ft
LIBFT_PATH=Libft/
NAME=push_swap

CFLAGS=-Wall -Werror -Wextra -pedantic-errors -O2

SRCS=main.c quick_sort.c

OBJS=main.o quick_sort.o

all : libft $(NAME)

libft :
	cd $(LIBFT_PATH) && $(MAKE) all # Let's build the Libft

$(NAME) : $(OBJS)
	$(CC) -L$(LIBFT_PATH) $(OBJS) -l$(LIBFT_NAME) -o $(NAME) -no-pie

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

main.o : main.c quick_sort.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c main.c

quick_sort.o : quick_sort.c quick_sort.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c quick_sort.c

.PHONY: all clean fclean re libft
