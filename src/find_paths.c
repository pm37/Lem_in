/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/10 18:40:52 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_visited(t_room *room)
{
	return (room->visited == true);
}

static void		get_shortest_path(t_anthill *anthill)
{
	t_list	*path;
	t_list	*steps;
	t_list	*room;
	t_list	*previous;

	path = anthill->paths;
	previous = NULL;
	while (path)
	{
		steps = ((t_path *)path->content)->steps;
		room = steps->content;
		if (((t_room *)room->content)->end == 1
		|| ((t_path *)path->content)->explored == true)
		{
			if (previous)
				previous->next = path->next;
			else
				anthill->paths = anthill->paths->next;
			path->next = NULL;
			ft_lstrev(&((t_path *)path->content)->steps);
			ft_lstprepend(&anthill->good_paths, path);
			break ;
		}
		previous = path;
		path = path->next;
	}
}
//distance_to_end a faire

static t_list	*closest_to_end(t_anthill *anthill
				, t_list *target, t_list *good_path, t_list *room)
{
	int		distance;
	int		min;
	t_list	*ptr;
	t_list	*result;
	t_list	*step;

	result = NULL;
	while (good_path)
	{
   		step = ((t_path *)good_path->content)->steps;
		while (step)
		{
			ptr = step->content;
			if (ptr == room)
			{
				distance = get_distance_to_end(good_path);
				if (distance < min)
				{
					min = distance;
					result = ptr;	
				}
			}
			step = step->next;
		}
		good_path = good_path->next;
	}
	return (result);
}

static int		relink(t_anthill *anthill, t_list *target, t_list *good_path, t_list *room)
{
	t_list	*step;
	t_list	*ptr;

	while (good_path)
	{
   		step = ((t_path *)good_path->content)->steps;
		while (step)
		{
			ptr = step->content;
			if (ptr == room)
			{
				((t_path *)target->content)->explored = true;
				if (!(add_step(anthill, &((t_path *)target->content)->steps
				, closest_to_end(anthill, target, good_path, room))))
					return (0);
				((t_path *)target->content)->len++;
				return (1);
			}
			step = step->next;
		}
		good_path = good_path->next;
	}
	return (0);
}

static int		complete_paths(t_anthill *anthill)
{
	t_list	*path;
	t_list	*tunnel;
	t_list	*room;
	int		i;

	path = anthill->paths;
	while (path)
	{
		room = ((t_list *)((t_path *)(path->content))->steps->content);
		tunnel = ((t_room *)(room->content))->tunnels;
		i = 0;
		while (tunnel)
		{
			room = tunnel->content;
			if (i >= 1 && !room_visited(room->content))
			{
				if (!add_path(anthill, path, room))
					return (0);
			}
			else if (!room_visited(room->content) && ++i)
			{
				if (!(add_step(anthill, &((t_path *)path->content)->steps, room)))
					return (0);
				((t_path *)path->content)->len++;
			}
			else if (room_visited(room->content)
			&& relink(anthill, path, anthill->good_paths, room))
				break ;
			tunnel = tunnel->next;
		}
		path = path->next;
	}
	return (1);
}

static int		end_found(t_anthill *anthill)
{
	t_list	*path;
	t_list	*steps;
	t_list	*room;

	path = anthill->paths;
	while (path)
	{
		steps = ((t_path *)path->content)->steps;
		room = steps->content;
		if (((t_room *)room->content)->end == 1)
		{
			((t_path *)path->content)->explored = true;
			((t_room *)room->content)->visited = false;
			return (1);
		}
		path = path->next;
	}
	return (0);
}

static int		all_paths_explored(t_list *path)
{
	int		paths_count;
	int		explored;

	explored = 0;
	paths_count = 0;
	while (path)
	{
		if (((t_path *)path->content)->explored == true)
			explored++;
		paths_count++;
		path = path->next;
	}
	return (explored == paths_count);
}

int				find_paths(t_anthill *anthill)
{
	if (!init_paths(anthill))
		return (0);


		while (!end_found(anthill))
		{
			if (!(complete_paths(anthill)))
				return (0);	
		}
		get_shortest_path(anthill);
	
	while (anthill->paths)
	{
		if (!(complete_paths(anthill)))
			return (0);	
		if (end_found(anthill))
			get_shortest_path(anthill);
		if (all_paths_explored(anthill->paths))
			break ;
		get_shortest_path(anthill);
	}



	
		if (all_paths_explored(anthill->good_paths))
			ft_putendl("ok");



	ft_putendl("ALL PATHS------------");
	print_paths(anthill->paths);
	ft_putendl("SHORTEST-------------");
	print_paths(anthill->good_paths);
	


	return (1);
}
