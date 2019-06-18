/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/17 15:50:22 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

static void		init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->start = NULL;
	anthill->end = NULL;
	anthill->room_qty = 0;
	anthill->rounds = 0;
	anthill->rounds = INT_MAX;
	anthill->id = 0;
}

int				main(void)
{
	t_anthill	anthill;
//	t_list		*start;
//	t_list		*tunnel;
//	t_list		*room;

	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR")); // free everything
/*	start = anthill.start;
	tunnel = ((t_room *)start->content)->tunnels;
	while (tunnel)
	{
		room = ((t_tunnel *)tunnel->content)->room;
		ft_printf("usage = %d, name = %s\n"
		, ((t_tunnel *)tunnel->content)->usage
		, ((t_room *)room->content)->name);
		tunnel = tunnel->next;
	}*/
	if (!(find_paths(&anthill)))
		return (0);
	return (0);
}
