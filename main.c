/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 19:48:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/26 18:35:14 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define EMPTY -1
#define LEFT -1
#define RIGHT 1

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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc((sizeof(char) * len) + sizeof(char));
	if (!strjoin)
		return (NULL);
	while (*s1)
		strjoin[i++] = *(s1++);
	while (*s2)
		strjoin[i++] = *(s2++);
	strjoin[i] = '\0';
	return (strjoin);
}

bool push(t_stack *stack, t_value value)
{
	if (stack->top >= stack->size - 1)
		return false;
	stack->top++;
	stack->values[stack->top] = value.real_value;
	stack->simplified_values[stack->top] = value.simplified_value;
	return true;
}

t_pop pop(t_stack *stack)
{
	t_pop pop;

	if (stack->top == EMPTY)
		pop.error = true;
	else
	{
		pop.value.real_value = stack->values[stack->top];
		pop.value.simplified_value = stack->simplified_values[stack->top];
		stack->top--;
		pop.error = false;
	}
	return pop;
}

void swap(t_stack *stack)
{
	int tmp;
	int tmp_simplified;

	if (stack->size > 1)
	{
		tmp = stack->values[stack->top];
		tmp_simplified = stack->simplified_values[stack->top];
		stack->values[stack->top] = stack->values[stack->top - 1];
		stack->simplified_values[stack->top] = stack->simplified_values[stack->top - 1];
		stack->values[stack->top - 1] = tmp;
		stack->simplified_values[stack->top - 1] = tmp_simplified;
	}
}

void rotate_down(t_stack *stack)
{
	int tmp;
	int tmp_simplified;
	int i;
	
	i = 0;
	tmp = stack->values[i];
	tmp_simplified = stack->simplified_values[i];
	while (i < stack->top)
	{
		stack->values[i] = stack->values[i + 1];
		stack->simplified_values[i] = stack->simplified_values[i + 1];
		i++;
	}
	stack->values[i] = tmp;
	stack->simplified_values[i] = tmp_simplified;
}

void rotate_up(t_stack *stack)
{
	int tmp;
	int tmp_simplified;
	int i;
	
	i = stack->top;
	tmp = stack->values[i];
	tmp_simplified = stack->simplified_values[i];
	while (i)
	{
		stack->values[i] = stack->values[i - 1];
		stack->simplified_values[i] = stack->simplified_values[i - 1];
		i--;
	}
	stack->values[i] = tmp;
	stack->simplified_values[i] = tmp_simplified;
}

void	check_error(bool is_error)
{
	if (is_error)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

t_stack create_stack(size_t size)
{
	t_stack stack;

	stack.values = malloc(sizeof(*stack.values) * size);
	check_error(!stack.values);
	stack.simplified_values = malloc(sizeof(*stack.values) * size);
	check_error(!stack.simplified_values);
	stack.size = size;
	stack.top = -1;
	return stack;
}

void populate_stack(t_stack *stack, char **values)
{
	int value_num;
	t_value	new_value;
	bool push_status;

	new_value.simplified_value = -1;
	push_status = true;
	value_num = stack->size - 1;
	while (value_num >= 0)
	{
		new_value.real_value = atoi(values[value_num]);
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

void sort(t_stack *stack_a, t_stack *stack_b)
{
	int max_num = stack_a->size - 1;
	int max_bits = 0;

	while ((max_num >> max_bits) != 0) ++max_bits;

	int i = 0;
	while (i < max_bits)
	{
		int j = 0;
		while (j < stack_a->size)
		{
			int num = stack_a->simplified_values[stack_a->top];
			if (((num >> i) & 1) == 1)
			{
				rotate_up(stack_a);
				printf("ra\n");
			}
			else
			{
				push(stack_b, pop(stack_a).value);
				printf("pb\n");
			}
			j++;
		}

		while (stack_b->top != EMPTY)
		{
			push(stack_a, pop(stack_b).value);
			printf("pa\n");
		}

		i++;
	}
}

void print_stack(char* stack_name, t_stack stack)
{
	while (stack.top != EMPTY)
		printf("%d\n", pop(&stack).value.real_value); // TO-DO: rmv printf
	printf("-\n");
	printf("%s\n", stack_name);
	printf("\n");
}

void	simplify_stack(t_stack *stack)
{
	t_value value;

	int i = 0;
	while (i < stack->size)
	{
		int j = 0;
		value.simplified_value = 0;
		while (j < stack->size)
		{
			if (stack->values[i] > stack->values[j])
				value.simplified_value++;
			j++;
		}
		stack->simplified_values[i] = value.simplified_value;
		i++;
	}
}

bool	is_integer(char *str)
{
	int i;

	i = 0;
	if (str[0] == '-' && str[1]) i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
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
	len = strlen(str);
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
		if (strcmp(args[i], args[len]) == 0)
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
		new_str = strcat(strcat(new_str, " "), str[i]);
		i++;
	}
	
	return new_str;
}

int count_args(char *args)
{
	char *arg;	
	int count;

	count = 0;
	arg = strtok(args, " ");
	while (arg)
	{
		count++;	
		arg = strtok(NULL, " ");
	}
	return count;
}

void set_args(char **args, char *concatenated_args)
{
	char *arg;	
	int i;

	arg = strtok(concatenated_args, " ");
	i = 0;
	while (arg)
	{
		args[i] = arg;
		arg = strtok(NULL, " ");
		i++;
	}
}

int main(int argc, char **argv)
{
	t_stack stack_a;
	t_stack stack_b;
	size_t stack_size;
	char	*concatenated_args;
	char	**args;

	if (argc == 1) return (0);
	concatenated_args = lstrip(rstrip(concat_strs(argv + 1, argc - 1)));
	stack_size = count_args(strdup(concatenated_args));
	args = malloc(sizeof(*args) * (stack_size + 1));
	args[stack_size] = NULL;
	set_args(args, concatenated_args);
	check_args(args);

	// TO-DO: free stacks before all exits
	// TO-DO: replace atoi and other forbidden functions (rm includes to find)
	// TO-DO: make immutable variables const
	/* TO-DO: when pop and push check if stacks are empty:
	 * - if pop returns false don't push (edit: probably no need to do this)
	 */

	stack_a = create_stack(stack_size);
	stack_b = create_stack(stack_size);
	populate_stack(&stack_a, args);
	simplify_stack(&stack_a);

	if (!is_sorted(stack_a))
	{
		if (stack_size > 5)
			sort(&stack_a, &stack_b);
		else if (stack_size > 3)
			five_sort(&stack_a, &stack_b);
		else if (stack_size == 3)
			three_sort(&stack_a);
		else if (stack_size == 2)
			two_sort(&stack_a);
	}

	/*
	if (is_sorted(stack_a))
		print_stack("A", stack_a);
	else
		printf("stack couldn't be sorted!\n");
		*/

	// run with:
	// set ARG (ruby -e "print *(0...9).sort_by{rand}.join(' ')") | ./push_swap $ARG | ./checker_Mac $ARG

	return (0);
}
