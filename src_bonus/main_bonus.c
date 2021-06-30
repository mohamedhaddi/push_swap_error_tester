/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:48:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 04:10:27 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	str_arr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;
	size_t	stack_size;
	char	**args;

	if (argc == 1)
		return (0);
	args = parse_args(argv, argc);
	stack_size = str_arr_len(args);
	stack_a = create_stack(stack_size);
	stack_b = create_stack(stack_size);
	populate_stack(&stack_a, args);
	free_double_pointer(args);
	simplify_stack(&stack_a);
	return (check_operations(&stack_a, &stack_b));
}
