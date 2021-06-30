/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:57:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 04:11:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define EMPTY -1

typedef struct s_data
{
	char		**args;
	int			args_state;
}				t_data;

typedef struct s_stack
{
	int			*values;
	int			*simplified_values;
	int			size;
	int			top;
}				t_stack;

typedef struct s_value
{
	int			real_value;
	int			simplified_value;
}				t_value;

typedef struct s_pop
{
	t_value		value;
	bool		error;
}				t_pop;

void			check_error(bool is_error);
bool			is_integer(char *str);
bool			is_over_int(char *str);
char			*strip_one_plus(char *s);
bool			is_duplicate(int len, char **args);
char			*remove_trailing_zeros(char *s);
t_stack			create_stack(size_t size);
void			populate_stack(t_stack *stack, char **values);
char			**parse_args(char **argv, int argc);
bool			push(t_stack *stack, t_value value);
t_pop			pop(t_stack *stack);
void			swap(t_stack *stack);
void			destroy_stack(t_stack *stack);
void			free_double_pointer(char **ptr);
void			simplify_stack(t_stack *stack);
bool			is_sorted(t_stack stack);
bool			is_over_int(char *str);
void			rotate_down(t_stack *stack);
void			rotate_up(t_stack *stack);
void			run_operations(
					t_stack *stack_a,
					t_stack *stack_b,
					char **user_ops,
					int count_ops);
char			*ft_getline(void);
bool			is_rotate_a(char *operation);
bool			is_rotate_b(char *operation);
bool			is_reverse_rotate_a(char *operation);
bool			is_reverse_rotate_b(char *operation);
int				check_operations(t_stack *stack_a, t_stack *stack_b);

#endif
