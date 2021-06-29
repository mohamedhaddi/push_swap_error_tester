/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_sort_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:13:49 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/29 20:06:40 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

bool	smaller_in_top(int *arr)
{
	return (arr[2] < arr[1] && arr[2] < arr[0]);
}

bool	bigger_in_top(int *arr)
{
	return (arr[2] > arr[1] && arr[2] > arr[0]);
}

bool	smaller_in_middle(int *arr)
{
	return (arr[1] < arr[2] && arr[1] < arr[0]);
}

bool	bigger_in_bottom(int *arr)
{
	return (arr[0] > arr[2] && arr[0] > arr[1]);
}

bool	bigger_in_middle(int *arr)
{
	return (arr[1] > arr[2] && arr[1] > arr[0]);
}
