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
LIBRARIES := -Llibft -lft
INCLUDE_DIRS := libft \
				mlc \
				operations \
				stacks \
				sort \
				execute \
				predict \
				general_utils \
				includes \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := push_swap
SRCS := push_swap.c \
		stacks/iterate_stacks_utils.c \
		stacks/prepare_stacks.c \
		stacks/print_stacks.c \
		stacks/stack_last.c \
		stacks/stack_push.c \
		stacks/stack_rotate_backward.c \
		stacks/stack_rotate_forward.c \
		stacks/stack_second_to_last.c \
		stacks/stack_size.c \
		stacks/stack_swap.c \
		stacks/stackadd_back.c \
		stacks/stackadd_front.c \
		stacks/stackdelone.c \
		stacks/stackiter.c \
		stacks/stackmap.c \
		stacks/stacknew.c \
		stacks/stacks_clear.c \
		stacks/other_stacks_utils.c \
		operations/operations_push_swap.c \
		operations/operations_rotate_bwd.c \
		operations/operations_rotate_fwd.c \
		sort/cmds_utils.c \
		sort/cmds_utils2.c \
		sort/sort_algorithm.c \
		sort/sort_a_b.c \
		sort/merge_a_b.c \
		sort/limits.c \
		sort/sort_validations.c \
		sort/sort_parameters.c \
		predict/predict_limits.c \
		predict/predict_ramps.c \
		predict/pred_ini_rots.c \
		predict/pred_other_rots.c \
		predict/pred_rots_fwd.c \
		predict/pred_rots_bwd.c \
		general_utils/good_push_validation.c \
		general_utils/input.c \
		general_utils/init_utils.c \
		general_utils/other_cmds_utils.c \
		execute/execute_moves.c \
		execute/execute_moves2.c \
		execute/execute_utils.c

OBJS := $(SRCS:.c=.o)

all: libft $(NAME) 

libft:
	make -C libft/

mlc:
	make -C mlc/

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(NAME) : $(OBJS) 
	$(CC) $(FLAGS) $^ $(LIBRARIES) -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft/ clean

fclean: clean
		rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: libft minilibx all bonus clean fclean re
