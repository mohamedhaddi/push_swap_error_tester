/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:48:05 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 20:04:22 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	check_args(char **args)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		check_error(ft_strncmp(args[i], "+-", 2) == 0);
		if (ft_strncmp(args[i], "00", 2) == 0
			|| ft_strncmp(args[i], "+", 1) == 0)
		{
			tmp = ft_strdup(remove_trailing_zeros(strip_one_plus(args[i])));
			free(args[i]);
			args[i] = tmp;
		}
		check_error(args[i][0] == '\0');
		check_error(!is_integer(args[i]));
		check_error(is_over_int(args[i]));
		check_error(is_duplicate(i, args));
		i++;
	}
}

int	get_total_size(char **str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		size += ft_strlen(str[i]);
		i++;
	}
	return (size);
}

char	*concat_strs(char **str, int space_count)
{
	int		i;
	char	*new_str;
	char	*new_str_space;

	new_str = malloc(sizeof(*new_str)
			* (get_total_size(str) + space_count + 1));
	check_error(!new_str);
	*new_str = '\0';
	i = 0;
	while (str[i])
	{
		new_str_space = ft_strjoin(new_str, " ");
		check_error(!new_str_space);
		free(new_str);
		new_str = ft_strjoin(new_str_space, str[i]);
		check_error(!new_str);
		free(new_str_space);
		i++;
	}
	return (new_str);
}

void	check_empty_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		check_error(argv[i][0] == '\0');
		i++;
	}
}

char	**parse_args(char **argv, int argc)
{
	char	*concatenated_args;
	char	**args;

	check_empty_args(argv);
	concatenated_args = concat_strs(argv + 1, argc - 1);
	check_error(!concatenated_args);
	args = ft_split(concatenated_args, ' ');
	check_error(!concatenated_args);
	free(concatenated_args);
	check_args(args);
	return (args);
}
