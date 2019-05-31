/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:49:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/31 13:51:32 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_steps(t_list *steps)
{
	t_list	*step;
	t_list	*room;

	step = steps;
	while (step)
	{
		room = step->content;
		ft_printf("%s%c"
		, ((t_room *)(room->content))->name
		, step->next ? '-' : '\n');
		step = step->next;
	}
}

void			print_paths(t_list *paths)
{
	t_list	*path;
	t_list	*steps;

	path = paths;
	while (path)
	{
		steps = ((t_path *)(path->content))->steps;
		print_steps(steps);
		path = path->next;	
	}
}

