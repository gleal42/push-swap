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
LIBRARIES := -Llibft -lft -Lmlc -lmlc 
INCLUDE_DIRS := libft \
				mlc \
				operations \
				sort \
				stacks \
				utils \
				includes \
				validations \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := push_swap
SRCS := push_swap.c \
		stacks/prepare_stacks.c \
		stacks/print_stacks.c \
		stacks/stack_last.c \
		stacks/stack_push.c \
		stacks/stack_rotate_backward.c \
		stacks/stack_rotate_forward.c \
		stacks/stack_seccond_to_last.c \
		stacks/stack_size.c \
		stacks/stack_swap.c \
		stacks/stackadd_back.c \
		stacks/stackadd_front.c \
		stacks/stackdelone.c \
		stacks/stackiter.c \
		stacks/stackmap.c \
		stacks/stacknew.c \
		stacks/stacks_clear.c \
		validations/input_validations.c \
		operations/operations_push_swap.c \
		operations/operations_rotate_bwd.c \
		operations/operations_rotate_fwd.c \
		sort/execute_moves.c \
		sort/execute_moves2.c \
		sort/limits.c \
		sort/predict_limits.c \
		sort/predict_ramps.c \
		sort/sort_a_b_mvs.c \
		sort/merge_a_b_mvs.c \
		sort/sort_algorithm.c \
		sort/sort_validations.c \
		sort/sort_parameters.c \
		utils/get_info.c \
		utils/init_utils.c \
		utils/stacks_utils.c \
		utils/other_utils.c \
		utils/pred_rots.c \
		utils/pred_ini_rots.c \
		utils/prepare_moves_utils.c \
		utils/prepare_moves_utils2.c \
		utils/sort_algorithm_utils.c \

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
