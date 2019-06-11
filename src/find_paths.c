/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/11 15:08:42 by bwan-nan         ###   ########.fr       */
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
		if (((t_room *)room->content)->end == 1)
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
	while (max_flow--)
	{
		ft_putendl("ok");
		if (!init_paths(anthill))
			return (0);
		while (!end_found(anthill))
		{
			if (!(complete_paths(anthill)))
				return (0);	
		}
		get_shortest_path(anthill);
		if (max_flow)
			clean_paths(anthill);
	}

	get_shortest_path(anthill);
	ft_putendl("ALL PATHS------------");
	print_paths(anthill->paths);
	ft_putendl("SHORTEST-------------");
	print_paths(anthill->good_paths);


	return (1);
}
