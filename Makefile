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
				includes
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := push_swap
SRCS := push_swap.c \
		utils/push_swap_utils.c \
		sort_operations/push_swap_utils.c
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
