/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:48:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/28 17:21:02 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

#define EMPTY -1

typedef struct s_stack {
	int *values;
	int size;
	int top;
} t_stack;

typedef struct s_pop {
	int value;
	bool error;
} t_pop;

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

bool push(t_stack *stack, int value)
{
	if (stack->top >= stack->size - 1)
		return false;
	stack->top++;
	stack->values[stack->top] = value;
	return true;
}

t_pop pop(t_stack *stack)
{
	t_pop pop;

	if (stack->top == EMPTY)
		pop.error = true;
	else
	{
		pop.value = stack->values[stack->top];
		stack->top--;
		pop.error = false;
	}
	return pop;
}

void swap(t_stack *stack)
{
	int tmp;

	if (stack->top > 1)
	{
		tmp = stack->values[stack->top];
		stack->values[stack->top] = stack->values[stack->top - 1];
		stack->values[stack->top - 1] = tmp;
	}
}

void rotate_down(t_stack *stack)
{
	int tmp;
	int i;
	
	i = 0;
	tmp = stack->values[i];
	while (i < stack->top)
	{
		stack->values[i] = stack->values[i + 1];
		i++;
	}
	stack->values[i] = tmp;
}

void rotate_up(t_stack *stack)
{
	int tmp;
	int i;
	
	i = stack->top;
	tmp = stack->values[i];
	while (i)
	{
		stack->values[i] = stack->values[i - 1];
		i--;
	}
	stack->values[i] = tmp;
}

void	check_error(bool is_error)
{
	if (is_error)
	{
		write(2, "Error\n", 6);
		exit(255);
	}
}

t_stack create_stack(size_t size)
{
	t_stack stack;

	stack.values = malloc(sizeof(*stack.values) * size);
	check_error(!stack.values);
	stack.size = size;
	stack.top = -1;
	return stack;
}

void populate_stack(t_stack *stack, char **values)
{
	int value_num;
	int	new_value;
	bool push_status;

	push_status = true;
	value_num = stack->size - 1;
	while (value_num >= 0)
	{
		new_value = ft_atoi(values[value_num]);
		push_status = push(stack, new_value);
		value_num--;
	}
}

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

void two_sort(t_stack *stack_a)
{
	rotate_up(stack_a);
	printf("ra\n");
}

void three_sort(t_stack *stack_a)
{
	if (smaller_in_top(stack_a->values))
	{
		rotate_down(stack_a);
		printf("rra\n");
		swap(stack_a);
		printf("sa\n");
	}
	else if (smaller_in_middle(stack_a->values))
	{
		if (bigger_in_top(stack_a->values))
		{
			rotate_up(stack_a);
			printf("ra\n");
		}
		else if (bigger_in_bottom(stack_a->values))
		{
			swap(stack_a);
			printf("sa\n");
		}
	}
	else
	{
		if (bigger_in_middle(stack_a->values))
		{
			rotate_down(stack_a);
			printf("rra\n");
		}
		else if (bigger_in_top(stack_a->values))
		{
			rotate_up(stack_a);
			printf("ra\n");
			swap(stack_a);
			printf("sa\n");
		}
	}
}

bool is_sorted(t_stack stack)
{
	int i = 0;

	while (i < stack.top)
	{
		if (stack.values[i] < stack.values[i + 1])
			return false;
		i++;
	}
	return true;
}

int	get_smallest_val_index(t_stack *stack)
{
	int i;
	int smallest;
	int smallest_index;

	i = 0;
	smallest_index = 0;
	smallest = 2147483647;
	while (i <= stack->top)
	{
		if (stack->values[i] < smallest)
		{
			smallest = stack->values[i];
			smallest_index = i;
		}
		i++;
	}
	return smallest_index;
}

void bring_smallest_to_top(t_stack *stack_a, int smallest_val_index)
{
	if (smallest_val_index == 0)
	{
		rotate_down(stack_a);
		printf("rra\n");
	}
	else if (smallest_val_index == 1)
	{
		rotate_down(stack_a);
		printf("rra\n");
		rotate_down(stack_a);
		printf("rra\n");
	}
	else if (smallest_val_index == 2)
	{
		if (stack_a->top == 4)
		{
			rotate_up(stack_a);
			printf("ra\n");
		}
		swap(stack_a);
		printf("sa\n");
	}
	else if (stack_a->top == 4 && smallest_val_index == 3)
	{
		swap(stack_a);
		printf("sa\n");
	}
}

void five_sort(t_stack *stack_a, t_stack *stack_b)
{
	int i;
	int smallest_val_index;

	while (!is_sorted(*stack_a))
	{
		i = 0;
		while (i < stack_a->size - 3)
		{
			smallest_val_index = get_smallest_val_index(stack_a);
			bring_smallest_to_top(stack_a, smallest_val_index);
			push(stack_b, pop(stack_a).value);
			printf("pb\n");
			i++;
		}
		if (!is_sorted(*stack_a))
			three_sort(stack_a);
		while (i)
		{
			push(stack_a, pop(stack_b).value);
			printf("pa\n");
			i--;
		}
	}
}

void print_stack(char* stack_name, t_stack stack)
{
	while (stack.top != EMPTY)
		printf("%d\n", pop(&stack).value); // TO-DO: rmv printf
	printf("-\n");
	printf("%s\n", stack_name);
	printf("\n");
}

bool	is_integer(char *str)
{
	int i;

	i = 0;
	if (str[0] == '-' && str[1]) i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

bool	is_over_int(char *str)
{
	int i;
	int j;
	int len;
	bool is_negative;
	char* max_int = "2147483647";
	char last_digit = '7';

	i = 0;
	j = 0;
	len = ft_strlen(str);
	is_negative = str[i] == '-';
	if (is_negative) last_digit = '8';
	if (is_negative) i++;
	if (is_negative && len > 11) return true;
	if (is_negative && len < 11) return false;
	if (!is_negative && len > 10) return true;
	if (!is_negative && len < 10) return false;

	while (i < len - 1)
	{
		if (str[i] > max_int[j]) return true;
		else if (str[i] < max_int[j]) return false;
		i++;
		j++;
	}

	if (str[i] > last_digit) return true;

	return false;
}

char    *rstrip(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    i--;
    while (i > 0)
    {
        if (s[i] == ' ')
        {
            s[i] = '\0';
            i--;
        }
        else
            break ;
    }
    return (s);
}

char    *lstrip(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == ' ')
            i++;
        else
            break ;
    }
    return (s + i);
}

char	*strip_one_plus(char *s)
{
	if (s[0] == '+')
		s++;
	return s;
}

bool	is_duplicate(int len, char **args)
{
	int i;	

	i = 0;
	while (i < len)
	{
		if (ft_strcmp(args[i], args[len]) == 0)
			return true;
		i++;
	}
	return false;
}

char *remove_trailing_zeros(char *s)
{
	int i;

	i = 0;
	while (s[i] == '0')
		i++;
	if (i && s[i] == '\0')
		return s + (i - 1);
	return s + i;
}

void	check_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		check_error(ft_strlen(args[i]) > 1 && ft_strncmp(args[i], "+-", 2) == 0);
		args[i] = remove_trailing_zeros(strip_one_plus(args[i]));
		check_error(args[i][0] == '\0');
		check_error(!is_integer(args[i]));
		check_error(is_over_int(args[i]));
		check_error(is_duplicate(i, args));
		i++;
	}
}

int get_total_size(char **str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_strlen(str[i]);
		i++;
	}

	return size;
}

char	*concat_strs(char **str, int space_count)
{
	int i;
	char *new_str;

	new_str = malloc(sizeof(*new_str) * (get_total_size(str) + space_count + 1));
	*new_str = '\0';
	i = 0;
	while (str[i])
	{
		new_str = ft_strjoin(ft_strjoin(new_str, " "), str[i]);
		i++;
	}
	
	return new_str;
}

int	ft_double_ptr_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

void	check_empty_arg(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		check_error(argv[i][0] == '\0');
		i++;
	}
}

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

int main(int argc, char **argv)
{
	t_stack stack_a;
	t_stack stack_b;
	size_t stack_size;
	char	*concatenated_args;
	char	**args;
	char *operation;
	char *concat_user_ops;
	char **user_ops;
	char *tmp;
	int count_ops;
	int i;

	if (argc == 1) return (0);
	check_empty_arg(argv);
	concatenated_args = lstrip(rstrip(concat_strs(argv + 1, argc - 1)));
	args = ft_split(concatenated_args, ' ');
	stack_size = ft_double_ptr_len(args);
	check_args(args);

	stack_a = create_stack(stack_size);
	stack_b = create_stack(stack_size);
	populate_stack(&stack_a, args);

	// TO-DO:
	// - free stacks before all exits
	// - free strjoin strdup split and others

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

	if (stack_a.top == -1)
		printf("KO\n");
	else if (is_sorted(stack_a) && stack_a.top == stack_a.size - 1)
		printf("OK\n");
	else
		printf("KO\n");

	/* run with:
	set A (ruby -e "puts *(0...9).to_a.shuffle.join(' ')"); ./push_swap $A | ./checker_Mac $A
	*/

	return (EXIT_SUCCESS);
}
