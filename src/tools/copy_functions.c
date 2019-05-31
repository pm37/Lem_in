/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:05:00 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/31 15:05:51 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		copy_steps(void *dest, void *src)
{
	dest = src;
	return (1);
}

int		copy_path(void *dest, void *src)
{
	t_list	*src_list;
	t_list	*dest_list;
	t_path	*a;
	t_path	*b;

	src_list = (t_list *)src;
	dest_list = (t_list *)dest;
	a = ((t_path *)(src_list->content));
	b = ((t_path *)(dest_list->content));
	b->len = a->len;
	if (!(b->steps = ft_lstcpy(a->steps, copy_steps)))
		return (0);
	return (1);
}
