/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/04 12:15:33 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_visited(t_room *room)
{
	return (room->visited == true);
}
/*
static int		get_shortest_path(t_anthill *anthill)
{
	t_list	*path;
	t_list	*steps;
	t_list	*room;

	path = anthill->paths;
	while (path)
	{
		steps = ((t_path *)path->content)->steps;
		room = steps->content;
		if (room->end != 1)
			ft_lstdelone
		path = path->next;
	}
}
*/
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
			else if (!room_visited(room->content))
			{
				if (!(add_step(&((t_path *)(path->content))->steps, room)))
					return (0);
				i++;
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
			return (1);
		path = path->next;
	}
	return (0);
}

int				find_paths(t_anthill *anthill)
{
	if (!init_paths(anthill))
		return (0);
	while (!end_found(anthill))
		if (!(complete_paths(anthill)))
				return (0);
	//get_shortest_path(anthill->paths);
	print_paths(anthill->paths);
	return (1);
}
