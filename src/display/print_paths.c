/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:49:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/10 14:33:06 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_steps(t_list *steps)
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
	int		i;

	path = paths;
	i = 0;
	while (path && ++i)
	{
		ft_printf("ID: %d, STOP = %s, len = %d\n", i, 
		((t_path *)path->content)->stop ? "true" : "false", ((t_path *)path->content)->len);
		steps = ((t_path *)(path->content))->steps;
		print_steps(steps);
		path = path->next;	
	}
}

