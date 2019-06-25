/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:19:06 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/21 14:31:09 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int 	add_to_queue(t_list **queue, t_list *room)
{
	t_list		new;
	t_list		*node;
	t_list		*from;

	if (!(node = ft_lstnew(&new, sizeof(t_list))))
		return (0);
	from = (*queue)->content;
	node->content = (void *)room;
	ft_lstappend(queue, node);
	return (1);
}

static bool 	tunnel_is_usable(t_list *current, t_list *tunnel, t_list *end)
{
	t_list		*room;
	t_room		*dest;
	t_room 		*src;
	int		usage;

	src = (t_room *)current->content;
	room = ((t_tunnel *)tunnel->content)->room;
	dest = (t_room *)room->content;
	usage = ((t_tunnel *)tunnel->content)->usage;
	if (usage != -1 && dest->end != 0 && src->path_id != dest->path_id
	&& !dest->visited && dest->path_id != 0 && going_to_deviate(current, room))
		return (deviation_reaches_end(room, end));
	return (!dest->visited && usage != -1 && dest->end != 0
	&& !(src->deviation && usage == 0));
}

int 		complete_queue(t_list *queue, t_list *end)
{
	t_list	*tunnel;
	t_list	*room;
	t_list	*current;

	current = (t_list *)queue->content;
	tunnel = ((t_room *)current->content)->tunnels;
	while (tunnel)
	{
		room = ((t_tunnel *)tunnel->content)->room;
		if (!tunnel_is_usable(current, tunnel, end))
		{
			tunnel = tunnel->next;
			continue ;
		}
		if (!add_to_queue(&queue, room))
			return (0);
		((t_room *)room->content)->previous = current;
		((t_room *)room->content)->visited = true;
		if (((t_room *)room->content)->end == 1)
			return (1);
		if (going_to_deviate(current, room))
			((t_room *)room->content)->deviation = true;
		tunnel = tunnel->next;
	}
	if (((t_room *)current->content)->deviation == true)
		((t_room *)current->content)->deviation = false;
	return (1);
}

int		init_queue(t_list **queue, t_list *start)
{
	t_list	new;

	if (!(*queue = ft_lstnew(&new, sizeof(t_list))))
		return (0);
	(*queue)->content = (void *)start;
	return (1);
}
