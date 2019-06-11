/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:53:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/11 15:00:45 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 					add_to_queue(t_list **queue, t_list *room)
{
	t_list	*new;
	t_list	elem;

	if (!(new = ft_lstnew(&elem, sizeof(t_list)))
		return (0);
	new->content = (void *)room;
	ft_lstappend(queue, new);
	return (1);
}

int 					init_paths(t_anthill *anthill, t_list *queue)
{
	t_list	*start;
	t_list	*tunnel;
	t_list	*room;

	start = anthill->start;
	tunnel = ((t_room *)start->content)->tunnels;
	while (tunnel)
	{
		room = tunnel->content;
		((t_room *)room->content)->previous = anthill->start;
		if (!add_to_queue(&queue, room))
			return (0);
		tunnel = tunnel->next;
	}
	return (1);
}
