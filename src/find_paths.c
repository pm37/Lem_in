/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/31 18:32:39 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"




static int		room_visited(t_room *room)
{
	return (room->visited == true);
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
			if (i > 1 && !room_visited(room->content)) //buggy
			{
				if (!add_path(anthill, path, room))
					return (0);
			}
			else if (!room_visited(room->content))
			{
				if (!(add_step(&((t_path *)(path->content))->steps, room)))
					return (0);
			}
			i++;
			tunnel = tunnel->next;
		}
		path = path->next;
	}
	return (1);
}

static int		end_found(t_list *paths)
{
	t_list	*elem;
	t_list	*steps;
	t_list	*room;

	elem = paths;
	while (elem)
	{
		steps = ((t_path *)elem->content)->steps;
		room = steps->content;
		if (ft_strequ(((t_room *)room->content)->name, "end"))
			return (1);
		elem = elem->next;
	}
	return (0);
}

int				find_paths(t_anthill *anthill)
{
	if (!init_paths(anthill))
		return (0);
	while (!end_found(anthill->paths))
		if (!(complete_paths(anthill)))
				return (0);
	print_paths(anthill->paths);
	return (1);
}
