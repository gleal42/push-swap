#ifndef STACKS_H
# define STACKS_H

# include "push_swap.h"

typedef struct s_stack
{
	int			*nbr;
	int		sorted_pos;
	struct s_stack	*next;
}				t_stack;

t_stack		*ft_stacknew(int nbr);
void		ft_stackadd_back(t_stack **stack, t_stack *new_stack);
void		ft_stacktadd_front(t_stack **stack, t_stack *new_stack);
int			ft_stacksize(t_stack *stack);
t_stack		*ft_stacklast(t_stack *lst);
void		ft_stackswap(t_stack **head);
int			is_nbr_in_stack(int nbr, t_stack *a);
void	 	ft_print_stack(t_stack *stack);
void		ft_stackdelone(t_stack *stack, void (*del)(void*));
void		ft_stackiter(t_stack *stack, void (*f)(void *));
t_stack		*ft_stackmap(t_stack *stack, void *(*f)(void *), void (*del)(void *));
void		ft_stacks_clear(t_stack **stack, void (*del)(void*));
void		ft_stackswap(t_stack **head);

#endif
