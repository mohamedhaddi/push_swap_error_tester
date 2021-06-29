/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:48:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 17:05:23 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	smaller_in_top(int *arr)
{
	return arr[2] < arr[1] && arr[2] < arr[0];
}

bool	bigger_in_top(int *arr)
{
	return arr[2] > arr[1] && arr[2] > arr[0];
}

bool	smaller_in_middle(int *arr)
{
	return arr[1] < arr[2] && arr[1] < arr[0];
}

bool	bigger_in_bottom(int *arr)
{
	return arr[0] > arr[2] && arr[0] > arr[1];
}

bool	bigger_in_middle(int *arr)
{
	return arr[1] > arr[2] && arr[1] > arr[0];
}

void print_stack(char* stack_name, t_stack stack)
{
	while (stack.top != EMPTY)
		printf("%d\n", pop(&stack).value.real_value); // TO-DO: rmv printf
	printf("-\n");
	printf("%s\n", stack_name);
	printf("\n");
}

int	str_arr_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

int main(int argc, char **argv)
{
	t_stack stack_a;
	t_stack stack_b;
	size_t stack_size;
	char	**args;

	if (argc == 1) return (0);
	args = parse_args(argv, argc);
	stack_size = str_arr_len(args);
	stack_a = create_stack(stack_size);
	stack_b = create_stack(stack_size);
	populate_stack(&stack_a, args);
	free_double_pointer(args);
	simplify_stack(&stack_a);

	if (!is_sorted(stack_a))
		sort(&stack_a, &stack_b, stack_size);

	destroy_stack(&stack_a);
	destroy_stack(&stack_b);

	return (EXIT_SUCCESS);
}
