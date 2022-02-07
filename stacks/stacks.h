#ifndef STACKS_H
# define STACKS_H

# include "push_swap.h"

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define BLK "\x1b[30m"
# define RESET "\x1B[0m"
# define B_BLACK "\x001b[30;1m"
# define B_RED "\x001b[31;1m"
# define B_GREEN "\x001b[32;1m"
# define B_YELLOW "\x001b[33;1m"
# define B_BLUE "\x001b[34;1m"
# define B_MAGENTA "\x001b[35;1m"
# define B_CYAN "\x001b[36;1m"
# define B_WHITE "\x001b[37;1m"
# define BACKG_BLACK "\x001b[40m"
# define BACKG_RED "\x001b[41m"
# define BACKG_GREEN "\x001b[42m"
# define BACKG_YELLOW "\x001b[43m"
# define BACKG_BLUE "\x001b[44m"
# define BACKG_MAGENTA "\x001b[45m"
# define BACKG_CYAN "\x001b[46m"
# define BACKG_WHITE "\x001b[47m"
# define BACKG_B_BLACK "\x001b[40;1m"
# define BACKG_B_RED "\x001b[41;1m"
# define BACKG_B_GREEN "\x001b[42;1m"
# define BACKG_B_YELLOW "\x001b[43;1m"
# define BACKG_B_BLUE "\x001b[44;1m"
# define BACKG_B_MAGENTA "\x001b[45;1m"
# define BACKG_B_CYAN "\x001b[46;1m"
# define BACKG_B_WHITE "\x001b[47;1m"

t_stack		*stacknew(int nbr);

t_stack		*stack_last(t_stack *lst);

void		stackadd_back(t_stack **stack, t_stack *new_stack);
void		stacktadd_front(t_stack **stack, t_stack *new_stack);
int			stacksize(t_stack *stack);
t_stack		*stack_second_to_last(t_stack *lst);
void		stack_swap(t_stack **head);
int			is_nbr_in_stack(int nbr, t_stack *a);
void		stackdelone(t_stack *stack, void (*del)(int *));
void		stackiter(t_stack *stack, void (*f)(int));
void		stack_swap(t_stack **head);

t_stack		*stackmap(t_stack *stack, int(*f)(int), void (*del)(int *));

void		stacks_clear(t_stack **stack, void (*del)(int *));

void		stack_push_from_to(t_stack **src, t_stack **dst);
void		stack_rotate_forward(t_stack **stack);
void		stack_rotate_backward(t_stack **stack);

void		print_single_stack(t_stack *stack);
void		print_both_stacks(t_stack *a, t_stack *b, int max_len);
#endif
