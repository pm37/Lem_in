/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:30:18 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/10 18:37:37 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	all_paths_stopped(t_anthill *ath)
{
	t_list	*path;

	path = ath->paths;
	while (path)
	{
		if (((t_path *)path->content)->stop == false)
		{
			//	ft_putendl("\non continue...");
			return (0);
		}
		path = path->next;
	}
	return (1);
}

static int	check_new_room(t_list *room, t_list *path)
{
	t_list	*step;

	step = ((t_path *)path->content)->steps;
	if ((((t_room *)room->content)->visited == 0)
			&& ((t_room *)room->content)->end == -1)
		return (1);
	if (((t_room *)room->content)->end == 0)
		return (0);
	if (((t_room *)room->content)->end == 1)
	{
		((t_path *)path->content)->stop = true;
		return (1);
	}
	while (step)
	{
		//ft_printf("step1, %d =? %d\n", ((t_room *)room->content)->id,
		//((t_room *)((t_list *)step->content)->content)->id);
		if (((t_room *)room->content)->id == ((t_room *)((t_list *)step->content)->content)->id)
		{
			return (0);
		}
		step = step->next;
	}
	//ft_putendl("stop appose dns check new room");
	((t_path *)path->content)->stop = true;
	//ft_putendl("check new room1");
	return (1);
}

static int	is_visited(t_list *room, t_list *path)
{
	t_list	*step;

	step = ((t_path *)path->content)->steps;
	if ((((t_room *)room->content)->visited == false)
			&& ((t_room *)room->content)->end == -1)
		return (1);
	if (((t_room *)room->content)->end == 0)
		return (0);
	if (((t_room *)room->content)->end == 1)
		return (1);
	step = step->next;
	while (step)
	{
		//ft_printf("room id = %d | step id = %d\n", ((t_room *)room->content)->id,
		//((t_room *)step->content)->id);
		if (((t_room *)room->content)->id == ((t_room *)((t_list *)step->content)->content)->id)
			return (0);
		step = step->next;
	}
	//ft_putendl("end of is_visited reached");
	return (1);
}

static int	complete_paths(t_anthill *ath)
{
	t_list	*path;
	t_list	*tunnel;
	t_list	*room;
	int		first;

	path = ath->paths;
	while (path)
	{
		if (((t_path *)path->content)->stop == false)
		{
			room = (t_list *)((t_path *)(path->content))->steps->content;
			tunnel = ((t_room *)(room->content))->tunnels;
			first = 1;
			if (tunnel->next == NULL)
			{
				((t_path *)path->content)->stop = true;
				((t_path *)path->content)->dead_end = true;
			}
			while (tunnel)
			{
				room = (t_list *)tunnel->content;
				if (first != 1 && is_visited(room, path))
				{
					//	ft_printf("add path with room %s\n", ((t_room *)room->content)->name);
					if (!add_path(ath, path, room))
						return (0);
					if (((t_room *)room->content)->end == 1
							|| ((t_room *)room->content)->visited == true)
					{
						//	ft_printf("on appose le stop avec la room %s\n", ((t_room *)room->content)->name);
						((t_path *)ath->paths->content)->stop = true;
					}
					else
					{
						((t_path *)ath->paths->content)->stop = false;
						((t_room *)room->content)->visited = true;
					}
				}
				else if (check_new_room(room, path) && first--)
				{
					//ft_printf("add step with room %s\n", ((t_room *)room->content)->name);
					if (!add_step(ath, &(((t_path *)path->content)->steps), room))
						return (0);
					((t_path *)path->content)->len++;
				}
				tunnel = tunnel->next;
			}
		}
		path = path->next;
	}
	return (1);
}

static void	remove_dead_ends(t_anthill *ath)
{
	t_list	*path;

	path = ath->paths;
	while (path)
	{
		if (((t_path *)path->content)->dead_end == true)
			ft_lstpop(&ath->paths, path, del_path);
		path = path->next;
	}
}

static void		transfer_good_paths(t_anthill *anthill)
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
		}
		previous = path;
		path = path->next;
	}
}

static int	room_found_in_good_path(t_list *path, t_list *good_path)
{
	t_list	*last_step;
	t_list	*last_room;
	t_list	*step;

	last_step = ((t_path *)good_path->content)->steps;
	last_room = (t_list *)last_step->content;
	if (((t_room *)last_room->content)->end != 1)
		return (0);
	step = ((t_path)path->content)->steps;
	last_step = ((t_path *)path->content)->steps;
	last_room = (t_list *)last_step->content;
	while (step)
	{
		if (((t_room *)last_room->content)->id == ((t_room *)((t_list *)step->content)->content)->id)
			return (1);
		step = step->next;
	}
	return (0);
}

static int	finish_paths(t_anthill *ath)
{
	t_list	*path;
	t_list	*elem;
	int		ret;

	ret = 0;
	path = ath->paths;
	while (path)
	{
		elem = ath->paths;
		while (elem)
		{
			if (room_found_in_good_path(elem, path))
			{
				if (!concat_path(path, elem))
					return (0);
				ret++;
			}
			elem = elem->next;
		}
		path = path->next;
	}
	if (ret)
		transfer_good_paths(ath);
	return (ret);
}

int			find_all_paths(t_anthill *ath)
{
	int ret;

	if (!init_paths(ath))
		return (0);
	while (!all_paths_stopped(ath))
	{
		//ft_putendl("avant complete_paths");
		if (!complete_paths(ath))
			return (0); //free everything...
		//print_paths(ath->paths);
		//ft_putendl("apres complete_paths");
	}
	ft_putendl("\n--- avant remove_dead_ends ---->");
	print_paths(ath->paths);
	remove_dead_ends(ath);
	transfer_good_paths(ath);
	while (ret = finish_paths(ath))
	{
		if (!ret)
			return (0);
	}
	//remove_wrongs_paths(ath);
	return (1);
}
