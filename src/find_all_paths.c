/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:30:18 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/07 16:47:14 by pimichau         ###   ########.fr       */
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
			return (0);
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
		if (((t_room *)room->content)->id == ((t_room *)step->content)->id)
			return (0);
		step = step->next;
	}
	((t_path *)path->content)->stop = true;
	return (1);
}

static int	is_visited(t_list *room, t_list *path)
{
	t_list	*step;

	step = ((t_path *)path->content)->steps;
	if ((((t_room *)room->content)->visited == 0)
		&& ((t_room *)room->content)->end == -1)
		return (1);
	if (((t_room *)room->content)->end == 0)
		return (0);
	if (((t_room *)room->content)->end == 1)
		return (1);
	step = step->next;
	while (step)
	{
		ft_printf("room id = %d | step id = %d\n", ((t_room *)room->content)->id, ((t_room *)step->content)->id);
		if (((t_room *)room->content)->id == ((t_room *)step->content)->id)
			return (0);
		step = step->next;
	}
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
			while (tunnel)
			{
				room = (t_list *)tunnel->content;
				if (first != 1 && is_visited(room, path))
				{
					if (!add_path(ath, path, room))
						return (0);
					if (((t_room *)room->content)->end == 1
					|| ((t_room *)room->content)->visited >= 1)
					{
						((t_path *)path->content)->stop = true;
					}
					else
					{
						(((t_room *)room->content)->visited)++;
						((t_path *)path->content)->stop = false;
					}
				}
				else if (check_new_room(room, path) && first--)
				{
					if (!add_step(ath, &((t_path *)path->content)->steps, room))
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

int			find_all_paths(t_anthill *ath)
{
	if (!init_paths(ath))
		return (0);
	while (!all_paths_stopped(ath))
	{
		ft_putendl("avant complete_paths");
		if (!complete_paths(ath))
			return (0); //free everything...
		print_paths(ath->paths);
		ft_putendl("apres complete_paths");
	}
	return (1);
}
