/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 03:57:37 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/30 04:04:32 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

/*
 * checking if stack_b is empty for two reasons:
 * 1. if a is sorted but not all initial elements are in it.
 * 2. if stack_a is empty (pb pb...) is_sorted() returns true, so
 * we should also check if stack_b is empty
 */
void	print_result(t_stack *stack_a, t_stack *stack_b)
{
	if (is_sorted(*stack_a) && stack_b->top == EMPTY)
		printf("OK\n");
	else
		printf("KO\n");
}

bool	is_valid_op(char *operation)
{
	char	**valid_ops;
	int		i;

	valid_ops = (char *[11]){
		"sa\n",
		"sb\n",
		"ss\n",
		"pa\n",
		"pb\n",
		"ra\n",
		"rb\n",
		"rr\n",
		"rra\n",
		"rrb\n",
		"rrr\n"};
	i = 0;
	while (i < 11)
	{
		if (ft_strcmp(operation, valid_ops[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	**get_operations(int *count_ops)
{
	char	*concat_user_ops;
	char	*operation;
	char	*tmp;
	char	**user_ops;

	concat_user_ops = malloc(sizeof(*concat_user_ops));
	*concat_user_ops = '\0';
	count_ops = 0;
	while (1)
	{
		operation = ft_getline();
		if (ft_strcmp(operation, "EOF") == 0)
			break ;
		check_error(!is_valid_op(operation));
		tmp = concat_user_ops;
		concat_user_ops = ft_strjoin(tmp, operation);
		free(tmp);
		count_ops++;
	}
	tmp = concat_user_ops;
	user_ops = ft_split(tmp, '\n');
	free(tmp);
	return (user_ops);
}

int	check_operations(t_stack *stack_a, t_stack *stack_b)
{
	int		count_ops;
	char	**user_ops;

	user_ops = get_operations(&count_ops);
	if (user_ops[0] == NULL)
	{
		if (is_sorted(*stack_a))
			printf("OK\n");
		else
			printf("KO\n");
		return (EXIT_SUCCESS);
	}
	run_operations(stack_a, stack_b, user_ops, count_ops);
	print_result(stack_a, stack_b);
	destroy_stack(stack_a);
	destroy_stack(stack_b);
	return (EXIT_SUCCESS);
}
