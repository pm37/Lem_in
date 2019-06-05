/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 19:04:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/05 17:18:44 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


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

static void		reverse_back(t_list *paths)
{
	while (paths)
	{
		ft_lstrev(&((t_path *)paths->content)->steps);
		paths = paths->next;
	}
}

int				check_dead_end(t_anthill *anthill)
{
	t_list	*path;
	t_list	*step;
	t_list	*tunnel;
	t_list	*room;
	int		visited;
	int		tunnel_qty;
	int		dead_end;

	path = anthill->paths;
	dead_end = 0;
	while (path)
	{
		step = ((t_path *)path->content)->steps->content; 
		tunnel = ((t_room *)step->content)->tunnels;
		visited = 0;
		tunnel_qty = 0;
		while (tunnel && ++tunnel_qty)
		{
			room = (t_list *)tunnel->content;
			visited += ((t_room *)room->content)->visited == true;
			tunnel = tunnel->next;
		}
		if (((t_room *)step->content)->end != 1 && tunnel_qty == visited)
			dead_end++;
		path = path->next;
	}
	return (ft_lstcount(anthill->paths) == dead_end);
}

void			clean_paths(t_anthill *anthill)
{
	t_list	*path;
	t_list	*shortest_path;
	t_list	*steps;
	t_list	*diff;
	t_list	*tmp;

	path = anthill->paths;
	shortest_path = ((t_path *)anthill->good_paths->content)->steps;
	while (path)
	{
		ft_lstrev(&((t_path *)path->content)->steps);
		steps = ((t_path *)path->content)->steps;
		if (common_first_step(steps, shortest_path))
		{
			tmp = path->next;
			diff = compare_steps(steps, shortest_path);
			reset_rooms(diff);
			anthill->visited--;
			ft_lstpop(&anthill->paths, path, del_path);
			path = tmp;
		}
		else
			path = path->next;
	}
	reverse_back(anthill->paths);
	((t_room *)anthill->end->content)->visited = false;
}
