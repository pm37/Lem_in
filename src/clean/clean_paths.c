/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 19:04:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/10 16:57:29 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
static int		common_first_step(t_list *steps, t_list *path)
{
	t_list	*room1;
	t_list	*room2;

	if (steps->next && path->next)
	{
		steps = steps->next;
		path = path->next;
		room1 = steps->content;
		room2 = path->content;
		if (((t_room *)room1->content == ((t_room *)room2->content)))
			return (1);
	}
	return (0);
}

static void		reset_rooms(t_list *steps)
{
	t_list	*room;

	while (steps)
	{
		room = steps->content;		
		((t_room *)room->content)->visited = false;
		steps = steps->next;
	}
}

void			reset_steps(t_anthill *anthill, t_list *steps, int reverse)
{
	t_list	*shortest_path;
	t_list	*path_steps;
	t_list	*diff;

	shortest_path = anthill->good_paths;
	while (shortest_path)
	{
		path_steps = ((t_path *)shortest_path->content)->steps;
		ft_lstrev(&steps);
		if (reverse && common_first_step(path_steps, steps))
		{
			diff = compare_steps(steps, path_steps);
			reset_rooms(diff);
			anthill->visited--;
		}
		else if (!reverse && common_first_step(path_steps, steps))
		{
			diff = compare_steps(path_steps, steps);
			reset_rooms(diff);
			anthill->visited--;
		}
		ft_lstrev(&steps);
		shortest_path = shortest_path->next;
	}
}

int				remove_relink(t_anthill *anthill, t_list *target
		, t_list *associated_path)
{
	t_list	*steps;
	t_list	*associated_steps;
	t_list	*room;
	t_list	*path;

	path = anthill->paths;
	while (path)
	{
		steps = ((t_path *)path->content)->steps;
		room = steps->content;
		if (room == target)
		{
			associated_steps = ((t_path *)associated_path->content)->steps;
			if (ft_lstcount(steps) > ft_lstcount(associated_steps))
			{
				reset_steps(anthill, steps, 1);
				ft_lstpop(&anthill->paths, path, del_path);
			}
			else
			{
				reset_steps(anthill, associated_steps, 1);
				ft_lstpop(&anthill->paths, associated_path, del_path);
			}
			return (1);	
		}
		path = path->next;
	}
	return (0);
}

void			remove_blocking_path(t_anthill *anthill)
{
	t_list	*path;
	t_list	*last_step;
	t_list	*room;
	t_list	*tunnel;
	char	*name;

	path = anthill->paths;
	while (path)
	{
		last_step = ((t_path *)path->content)->steps;
		room = last_step->content;
		name = ((t_room *)room->content)->name;
		tunnel = ((t_room *)room->content)->tunnels;
		while (tunnel)
		{
			room = tunnel->content;
			if (remove_relink(anthill, room, path))
				break ;
			tunnel = tunnel->next;
		}
		path = path->next;
	}
}

void			clean_paths(t_anthill *anthill)
{
	t_list	*path;
	t_list	*last_step;
	t_list	*room;
	t_list	*tunnel;
	int		clean;
	int		distance;

//	remove_blocking_path(anthill);
	path = anthill->paths;
	while (path)
	{
		last_step = ((t_path *)path->content)->steps;
		room = last_step->content;
		distance = ((t_room *)room->content)->dist_to_start;
		tunnel = ((t_room *)room->content)->tunnels;
		clean = 1;
		while (tunnel)
		{
			room = tunnel->content;
			if (((t_room *)room->content)->dist_to_start <= distance)
				clean = 0;

			tunnel = tunnel->next;
		}
		reset_steps(anthill, last_step, 0);
		if (clean || ft_lstcount(tunnel) == 1)
			ft_lstpop(&anthill->paths, path, del_path);
		path = path->next;
	}
	((t_room *)anthill->end->content)->visited = false;
}*/
