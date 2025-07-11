CC=cc
LIBFT_NAME=ft
LIBFT_PATH=Libft/
NAME=push_swap

CFLAGS=-Wall -Werror -Wextra -pedantic-errors -O0 -g3

SRCS=main.c quick_sort.c auxiliary.c stack_basis.c stack_ops.c sorting.c sort_aux.c args_parser.c

OBJS=main.o quick_sort.o auxiliary.o stack_basis.o stack_ops.o sorting.o sort_aux.o args_parser.o

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

main.o : main.c args_parser.h stack_basis.h sorting.h quick_sort.h libft.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c main.c

quick_sort.o : quick_sort.c quick_sort.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c quick_sort.c

auxiliary.o : auxiliary.c auxiliary.h libft.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c auxiliary.c

stack_basis.o : stack_basis.c stack_basis.h libft.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c stack_basis.c

stack_ops.o : stack_ops.c stack_ops.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c stack_ops.c

sorting.o : sorting.c sorting.h quick_sort.h auxiliary.h libft.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c sorting.c

args_parser.o : args_parser.c args_parser.h stack_basis.h auxiliary.h libft.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c args_parser.c

sort_aux.o : sort_aux.c sort_aux.h stack_basis.h auxiliary.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c sort_aux.c

.PHONY: all clean fclean re libft
