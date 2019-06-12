/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/12 16:41:23 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_visited(t_room *room)
{
	return (room->visited == true);
}

static void 	setflags_in_goodpath(t_list *path)
{
	t_list	*step;
	t_list 	*room;

	step = ((t_path *)path->content)->steps;
	while (step)
	{
		room = step->content;
		if (((t_room *)room->content)->end == -1)
			((t_room *)room->content)->in_goodpath = true;
		step = step->next;
	}
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
		if (((t_room *)room->content)->end == 1)
		{
			if (previous)
			previous->next = path->next;
			else
			anthill->paths = anthill->paths->next;
			path->next = NULL;
			ft_lstrev(&((t_path *)path->content)->steps);
			ft_lstprepend(&anthill->good_paths, path);
			setflags_in_goodpath(path);
			break ;
		}
		previous = path;
		path = path->next;
	}
}

static int 		get_next_step(t_anthill *anthill, t_list *path, t_list *tunnel)
{
	t_list	*room;
	bool 		in_goodpath;
	int 		i;

	i = 0;
	while (tunnel)
	{
		room = tunnel->content;
		in_goodpath = ((t_room *)room->content)->in_goodpath;
		if (i >= 1 && (!room_visited(room->content) || in_goodpath))
		{
			if (!add_path(anthill, path, room))
				return (0);
			((t_path *)path->content)->deviation = in_goodpath;
		}
		else if ((!room_visited(room->content) || in_goodpath) && ++i)
		{
			if (!(add_step(anthill, &((t_path *)path->content)->steps, room)))
				return (0);
			((t_path *)path->content)->len++;
			((t_path *)path->content)->deviation = in_goodpath;
		}
		tunnel = tunnel->next;
	}
	return (1);
}

static int 		start_deviation(t_anthill *anthill, t_list *path, t_list *room)
{
	t_list *previous;

	previous = ((t_room *)room->content)->previous;

	if (((t_room *)previous->content)->end != 0)
	{
		if (!(add_step(anthill, &((t_path *)path->content)->steps, room)))
			return (0);
		((t_path *)path->content)->deviation = false;
	}
	return (1);
}

static int 		continue_deviation(t_anthill *anthill, t_list *path, t_list *room)
{

}

static int		complete_paths(t_anthill *anthill)
{
	t_list	*path;
	t_list	*tunnels;
	t_list	*room;

	path = anthill->paths;
	while (path)
	{
		room = ((t_list *)((t_path *)(path->content))->steps->content);
		tunnels = ((t_room *)(room->content))->tunnels;
		if (((t_room *)room->content)->in_goodpath)
		{
			if (((t_path *)path->content)->deviation)
			{
				if (!start_deviation(anthill, path, room))
					return (0);
			}
			else
			{
				if (!continue_deviation(anthill, path, room))
					return (0);
			}
		}
		else if (!get_next_step(anthill, path, tunnels))
			return (0);
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
			((t_room *)room->content)->visited = false;
			anthill->residual_capacity++;
			return (1);
		}
		path = path->next;
	}
	return (0);
}

int				find_paths(t_anthill *anthill)
{
	int	max_flow;

	max_flow = anthill->max_flow;
	if (!init_paths(anthill))
	return (0);
	while (!end_found(anthill))
	{
		if (!(complete_paths(anthill)))
		return (0);
	}
	get_shortest_path(anthill);

	ft_putendl("ALL PATHS------------");
	print_paths(anthill->paths);
	ft_putendl("SHORTEST-------------");
	print_paths(anthill->good_paths);


	return (1);
}
