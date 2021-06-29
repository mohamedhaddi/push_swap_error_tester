/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:48:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 20:11:55 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

bool	is_valid_op(char *operation)
{
	char **valid_ops;
	int i;

	valid_ops = (char *[11]){"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};

	i = 0;
	while (i < 11)
	{
		if (ft_strcmp(operation, valid_ops[i]) == 0)
			return true;
		i++;
	}
	return false;
}

char	*ft_getline(void)
{
	char	c;
	char	*line;
	char	*tmp;

	line = malloc(1);
	*line = '\0';
	while (1)
	{
		if (!read(0, &c, 1))
		{
			tmp = line;
			line = ft_strjoin(tmp, "EOF");
			free(tmp);
			return (line);
		}
		tmp = line;
		line = ft_strjoin(tmp, (char [2]){c, '\0'});
		free(tmp);
		if (c == '\n')
			return (line);
	}
}

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
	if (!is_sorted(stack_a))
		sort(&stack_a, &stack_b, stack_size);
	destroy_stack(&stack_a);
	destroy_stack(&stack_b);

	// --------------------------------------------------------------
	
	char *concat_user_ops;
	int count_ops;
	char *operation;
	char *tmp;
	char **user_ops;

	concat_user_ops = malloc(sizeof(*concat_user_ops));
	*concat_user_ops = '\0';
	count_ops = 0;
	while (1)
	{
		operation = ft_getline();
		if (ft_strcmp(operation, "EOF") == 0) break ;
		check_error(!is_valid_op(operation));
		tmp = concat_user_ops;
		concat_user_ops = ft_strjoin(tmp, operation);
		free(tmp);
		count_ops++;
	}
	tmp = concat_user_ops;
	user_ops = ft_split(tmp, '\n');
	free(tmp);

	if (user_ops[0] == NULL)
	{
		if (is_sorted(stack_a))
			printf("OK\n");
		else
			printf("KO\n");
		return (EXIT_SUCCESS);
	}

	int i;
	i = 0;
	while (i < count_ops)
	{
		if (ft_strcmp(user_ops[i], "sa") == 0 || ft_strcmp(user_ops[i], "ss") == 0)
			swap(&stack_a);
		if (ft_strcmp(user_ops[i], "sb") == 0 || ft_strcmp(user_ops[i], "ss") == 0)
			swap(&stack_b);
		if (ft_strcmp(user_ops[i], "pa") == 0)
			push(&stack_a, pop(&stack_b).value);
		if (ft_strcmp(user_ops[i], "pb") == 0)
			push(&stack_b, pop(&stack_a).value);
		if (ft_strcmp(user_ops[i], "ra") == 0 || ft_strcmp(user_ops[i], "rr") == 0)
			rotate_up(&stack_a);
		if (ft_strcmp(user_ops[i], "rb") == 0 || ft_strcmp(user_ops[i], "rr") == 0)
			rotate_up(&stack_b);
		if (ft_strcmp(user_ops[i], "rra") == 0 || ft_strcmp(user_ops[i], "rrr") == 0)
			rotate_down(&stack_a);
		if (ft_strcmp(user_ops[i], "rrb") == 0 || ft_strcmp(user_ops[i], "rrr") == 0)
			rotate_down(&stack_b);
		i++;
	}

	//if (stack_a.top == -1)
	//	printf("KO\n");
	if (is_sorted(stack_a) && stack_b.top == EMPTY) // checking if stack_b is empty
													// for two reasons:
													// 1. if a is sorted but not all
													// initial elements are in it.
													// 2. if stack_a is empty (pb pb...)
													// is_sorted() returns true, so
													// we should also check if stack_b
													// is empty
		printf("OK\n");
	else
		printf("KO\n");

	return (EXIT_SUCCESS);
}
