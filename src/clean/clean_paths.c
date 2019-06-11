/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 19:04:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/11 15:02:32 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reset_rooms(t_list *room)
{
	while (room)
	{
		((t_room *)room->content)->visited = false;
		room = room->next;
	}
}

static void	block_entry(t_list *path)
{
	t_list	*room;
	t_list	*step;
	int	i;

	step = ((t_path *)path->content)->steps;
	i = 0;
	while (step && ++i)
	{
		room = step->content;
		if (i == 2)
			((t_room *)room->content)->visited = true;
		step = step->next;
	}
}

void		clean_paths(t_anthill *anthill)
{
	ft_lstdel(&anthill->paths, del_path);
	reset_rooms(anthill->rooms);
	block_entry(anthill->good_paths);
}
