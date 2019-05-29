/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/29 18:38:57 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->paths = NULL;
	anthill->start = NULL;
	anthill->end = NULL;
	anthill->room_qty = 0;
	anthill->path_ids = 0;
	anthill->paths_found = 0;
}

static void	print_paths(t_list *paths)
{
	t_list *elem;
	t_path *tmp2;
	t_list *tmp;

	elem = paths;
	while (elem)
	{
		tmp2 = (t_path *)elem->content;
		tmp =  tmp2->steps;
		ft_printf("path : %s\n", ((t_room *)(tmp->content))->name);
		elem = elem->next;
	}
}
/*
static void	print_anthill_rooms(t_anthill *anthill)
{
	t_list	*room;

	room = anthill->rooms;
	while (room)
	{
		ft_printf("room name : %s\n", ((t_room *)room->content)->name);
		room = room->next;
	}
}*/

int			main(void)
{
	t_anthill	anthill;

	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR")); // free everything
	//ft_printf("start name = %s\n", ((t_room *)(anthill.start->content))->name);
	//ft_printf("end name = %s\n", ((t_room *)(anthill.end->content))->name);
	/*if (!find_paths(&anthill, anthill.end,
	((t_room *)(anthill.end->content))->name))
		return (0); //free everything
	print_paths(anthill.paths);*/
	//print_anthill_rooms(&anthill);
	init_paths(&anthill);
	ft_printf("passe par la\n");
	find_paths_with_bfs(&anthill);
	ft_printf("passe par la\n");
	print_paths(anthill.paths);
	ft_printf("passe par la\n");
	return (0);
}
