/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:05:00 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/04 11:39:43 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		copy_steps(void *dest, void *src)
{
	dest = src;
	return (0);
}

int		copy_path(void *dest, void *src)
{
	t_path	*a;
	t_path	*b;

	a = (t_path *)src;
	b = (t_path *)dest;
	b->len = a->len;
	if (!(b->steps = ft_lstcpy(a->steps, copy_steps)))
		return (-1);
	return (0);
}
