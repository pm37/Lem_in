/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:43:17 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/02 12:42:31 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			update_data(t_anthill *anthill, unsigned long rounds
				, t_list **paths)
{
	t_list	*room;

	room = anthill->rooms;
	while (room)
	{
		((t_room *)room->content)->next = ((t_room *)room->content)->new_next;
		((t_room *)room->content)->path_id = ((t_room *)room->content)
		->new_path_id;
		((t_room *)room->content)->previous = NULL;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->dead_end = false;
		((t_room *)room->content)->new_next = NULL;
		((t_room *)room->content)->new_path_id = 0;
		room = room->next;
	}
	ft_lstrev(paths);
	if (anthill->option & DISPLAY_PATHS)
		print_paths(*paths);
	anthill->rounds = rounds;
}

static void		increment_sent_values(t_list *path)
{
	while (path)
	{
		((t_path *)path->content)->sent++;
		path = path->next;
	}
}

static t_list	*get_longest_path(t_list *path, unsigned int ant_qty)
{
	t_list			*head;
	unsigned int	ant_qty_out;
	int				path_len;

	if (!path->next)
		return (path);
	head = path;
	path_len = ((t_path *)path->content)->len;
	ant_qty_out = 0;
	path = path->next;
	while (path)
	{
		ant_qty_out += path_len - ((t_path *)path->content)->len + 1;
		path = path->next;
	}
	if (ant_qty_out < ant_qty)
		return (head);
	return (get_longest_path(head->next, ant_qty));
}

unsigned long	test_solution(t_anthill *anthill, t_list *paths
				, unsigned int ant_qty)
{
	t_list			*used_path;
	unsigned long	rounds;

	rounds = 0;
	used_path = paths;
	while (ant_qty > 0)
	{
		used_path = get_longest_path(used_path, ant_qty);
		increment_sent_values(used_path);
		ant_qty -= ft_lstcount(used_path);
		rounds++;
	}
	rounds += ((t_path *)used_path->content)->len - 1;
	if (anthill->option & DISPLAY_PATHS)
	{
		if (rounds >= anthill->rounds)
			ft_printf(
			"This solution would take {red}%ld rounds{nc}\n"
			, rounds);
		else
			ft_printf(
			"This solution would take {green}%ld rounds{nc}\n"
			, rounds);
	}
	return (rounds);
}
