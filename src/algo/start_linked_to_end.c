/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_linked_to_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:58:24 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/02 11:59:05 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		start_linked_to_end(t_list *start, t_list *end)
{
	t_list	*tunnel;
	t_list	*dest_room;

	tunnel = ((t_room *)start->content)->tunnels;
	while (tunnel)
	{
		dest_room = ((t_tunnel *)tunnel->content)->room;
		if (dest_room == end)
			return (true);
		tunnel = tunnel->next;
	}
	return (false);
}

bool		init_the_only_path(t_list **paths, t_anthill *anthill)
{
	t_path	path;
	t_list	*new_path;

	path.room = anthill->end;
	path.len = 1;
	path.sent = anthill->ant_qty;
	path.id = 1;
	path.complete = true;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (false);
	if (anthill->option & DISPLAY_PATHS)
	{
		ft_printf("{ul}{bold}Initialized 1 path:{nc}\n");
		ft_printf("{green}# 1:{nc} End\n");
	}
	ft_lstprepend(paths, new_path);
	return (true);
}
