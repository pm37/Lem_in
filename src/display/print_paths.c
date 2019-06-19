/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:49:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/17 15:49:26 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_path(t_list *room)
{
	ft_printf("PATH ID: %d\n", ((t_room *)room->content)->path_id);
	while (room)
	{
		ft_printf("%s%c"
		, ((t_room *)room->content)->name
		, ((t_room *)room->content)->next ? '-' : '\n');
		room = ((t_room *)room->content)->next;
	}
}

void		print_paths(t_list *start)
{
	t_list	*tunnel;
	t_list	*next_room;

	tunnel = ((t_room *)start->content)->tunnels;
	while (tunnel)
	{
		next_room = ((t_tunnel *)tunnel->content)->room;
		if (((t_tunnel *)tunnel->content)->usage == -1
		&& ((t_room *)next_room->content)->next)
			print_path(((t_tunnel *)tunnel->content)->room);
		tunnel = tunnel->next;
	}
}

void print_steps(t_list *room)
{
	ft_printf("Path id %d\n", ((t_room *)room->content)->path_id);
	while (room)
	{
		ft_printf("%s%c"
		, ((t_room *)room->content)->name
		, ((t_room *)room->content)->next ? '-' : '\n');
		room = ((t_room *)room->content)->next;
	}
}
