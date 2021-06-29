/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:57:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 17:14:46 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

#define EMPTY -1

typedef struct s_data {
	char **args;
	int args_state;
} t_data;

typedef struct s_stack {
	int *values;
	int *simplified_values;
	int size;
	int top;
} t_stack;

typedef struct s_value {
	int real_value;	
	int simplified_value;
} t_value;

typedef struct s_pop {
	t_value value;
	bool error;
} t_pop;

void	check_error(bool is_error);
bool	is_integer(char *str);
bool	is_over_int(char *str);
char	*strip_one_plus(char *s);
bool	is_duplicate(int len, char **args);
char *remove_trailing_zeros(char *s);
t_stack create_stack(size_t size);
void populate_stack(t_stack *stack, char **values);
char **parse_args(char **argv, int argc);
void rotate_up_and_print(t_stack *stack, char *operation);
void rotate_down_and_print(t_stack *stack, char *operation);
void push_and_print(t_stack *stack, t_value value, char *operation);
bool push(t_stack *stack, t_value value);
t_pop pop(t_stack *stack);
void	swap_and_print(t_stack *stack, char *operation);
void	destroy_stack(t_stack *stack);
void    free_double_pointer(char **ptr);
void	simplify_stack(t_stack *stack);
void bring_smallest_to_top(t_stack *stack_a, int smallest_val_index);
int	get_smallest_val_index(t_stack *stack);
bool	smaller_in_top(int *arr);
bool	bigger_in_top(int *arr);
bool	smaller_in_middle(int *arr);
bool	bigger_in_bottom(int *arr);
bool	bigger_in_middle(int *arr);

#endif
