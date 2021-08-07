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
				includes \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := push_swap
SRCS := push_swap.c \
		utils/push_swap_utils.c \
		sort_operations/sort_operations1.c \
		sort_operations/sort_operations2.c \
		sort_operations/sort_operations3.c \
		sort_operations/sort_algorithm.c \
		sort_operations/complex_algo.c \
		sort_operations/execute_moves.c \
		sort_operations/limit_check.c \
		stacks/isinstack.c \
		stacks/print_stacks.c \
		stacks/stackadd_back.c \
		stacks/stackadd_front.c \
		stacks/stackdelone.c \
		stacks/stackiter.c \
		stacks/stack_last.c \
		stacks/stack_seccond_to_last.c \
		stacks/stackmap.c \
		stacks/stacknew.c \
		stacks/stacks_clear.c \
		stacks/stack_size.c \
		stacks/stack_swap.c \
		stacks/stack_rotate_forward.c \
		stacks/stack_rotate_backward.c \
		stacks/stack_push.c

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
