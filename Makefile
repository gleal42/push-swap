# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/09 15:43:58 by gleal             #+#    #+#              #
#    Updated: 2021/06/22 21:28:28by gleal            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
FLAGS := -Wall -Wextra -Werror -g
INCLUDE_DIRS := libft \
				utils \
				sort_operations \
				stacks \
				. \
				includes
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := push_swap
SRCS := push_swap.c \
		utils/push_swap_utils.c \
		sort_operations/sort_operations.c \
		stacks/ft_isinstack.c \
		stacks/ft_print_stack.c \
		stacks/ft_stackadd_back.c \
		stacks/ft_stackadd_front.c \
		stacks/ft_stackdelone.c \
		stacks/ft_stackiter.c \
		stacks/ft_stacklast.c \
		stacks/ft_stackmap.c \
		stacks/ft_stacknew.c \
		stacks/ft_stacks_clear.c \
		stacks/ft_stacksize.c \
		stacks/ft_stackswap.c \
		stacks/ft_stack_push.c

OBJS := $(SRCS:.c=.o)

all: libft $(NAME) 

libft:
	make -C libft/

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(NAME) : $(OBJS) 
	$(CC) $(FLAGS) $^ -Llibft -lft -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft/ clean

fclean: clean
		rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: libft minilibx all bonus clean fclean re
