/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/20 16:29:32 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

static void 		reset_visited_rooms(t_list *dev_room
			, t_list *prev_room, t_list *queue, t_list *end)
{
	t_list	*room;

	while (queue)
	{
		room = queue->content;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->previous = NULL;
		queue = queue->next;
	}
	((t_room *)dev_room->content)->visited = false;
	((t_room *)prev_room->content)->visited = false;
	((t_room *)dev_room->content)->deviation = false;
	((t_room *)prev_room->content)->deviation = false;
	((t_room *)dev_room->content)->previous = NULL;
	((t_room *)prev_room->content)->previous = NULL;
	((t_room *)end->content)->visited = false;
	((t_room *)end->content)->deviation = false;
}

static bool 			deviation_reaches_end(t_list *deviation_room, t_list *end)
{
	t_list	*prev_room;
	t_list	*tunnel;
	t_list 	*queue;
	bool 		ret;

	queue = NULL;
	prev_room = NULL;
	tunnel = ((t_room *)deviation_room->content)->tunnels;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == 1)
		{
			prev_room = ((t_tunnel *)tunnel->content)->room;
			break ;
		}
		tunnel = tunnel->next;
	}
	if (((t_room *)prev_room->content)->end == 0)
		return (false);
	ret = false;
	if (((t_room *)prev_room->content)->visited == false
	&& ((t_room *)deviation_room->content)->dead_end == false)
	{
		((t_room *)deviation_room->content)->visited = true;
		((t_room *)prev_room->content)->visited = true;
		ret = bfs(prev_room, end, &queue);
		if (!ret)
			((t_room *)deviation_room->content)->dead_end = true;
		reset_visited_rooms(deviation_room, prev_room, queue, end);
		ft_lstdel(&queue, del_steps);
	}
	return (ret);
}

static bool 			tunnel_is_usable(t_list *current, t_list *tunnel, t_list *end)
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
	{
		return (deviation_reaches_end(room, end));
	}
	return (!dest->visited && usage != -1 && dest->end != 0
	&& !(src->deviation && usage == 0));
}

int 			going_to_deviate(t_list *current, t_list *room)
{
	t_room 	*src;
	t_room 	*dest;
	t_list	*tunnel;
	int 		tunnel_used;

	tunnel_used = 0;
	src = (t_room *)current->content;
	dest = (t_room *)room->content;
	tunnel = dest->tunnels;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == 1)
		{
			tunnel_used = 1;
			break ;
		}
		tunnel = tunnel->next;
	}
	return (!src->deviation && tunnel_used
	&& src->path_id != dest->path_id && dest->path_id != 0);
}

static int 			add_to_queue(t_list **queue, t_list *room)
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

static int 			complete_queue(t_list *queue, t_list *end)
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

static int			init_queue(t_list **queue, t_list *start)
{
	t_list	new;

	if (!(*queue = ft_lstnew(&new, sizeof(t_list))))
		return (0);
	(*queue)->content = (void *)start;
	return (1);
}

bool			bfs(t_list *start, t_list *end, t_list **queue)
{
	t_list		*head;
	t_list		*room;
	bool 			found_augmented_path;

	found_augmented_path = false;
	if (!init_queue(queue, start))
		return (false);
	((t_room *)start->content)->visited = true;
	head = *queue;
	while (*queue)
	{
		room = (*queue)->content;
		if (!complete_queue(*queue, end))
			return (false);
		if (((t_room *)end->content)->visited)
		{
			found_augmented_path = true;
			break ;
		}
		*queue = (*queue)->next;
	}
	*queue = head;
	return (found_augmented_path);
}

static t_list			*get_tunnel(t_list *src, t_list *dest)
{
	t_list	*tunnel;
	t_list	*room;

	tunnel = ((t_room *)src->content)->tunnels;
	while (tunnel)
	{
		room = ((t_tunnel *)tunnel->content)->room;
		if (room == dest)
			return (tunnel);
		tunnel = tunnel->next;
	}
	return (NULL);
}

static void set_usage(t_list *src, t_list *dest, bool is_previous)
{
	t_list	*tunnel;

	if (!(tunnel = get_tunnel(src, dest)))
		return ;
	if (((t_tunnel *)tunnel->content)->usage == 0 && is_previous)
		((t_tunnel *)tunnel->content)->usage = -1;
	else if (((t_tunnel *)tunnel->content)->usage == 0 && !is_previous)
		((t_tunnel *)tunnel->content)->usage = 1;
	else
		((t_tunnel *)tunnel->content)->usage = 0;
}

static void 			set_tunnels_usage(t_list *end)
{
	t_list	*room;
	t_list	*previous;

	room = end;
	while (room)
	{
		previous = ((t_room *)room->content)->previous;
		if (previous)
		{
			set_usage(previous, room, true);
			set_usage(room, previous, false);
		}
		room = ((t_room *)room->content)->previous;
	}
}

static void 				complete_path(t_list *path, t_list *room)
{
	t_list	*tunnel;
	t_list	*next_room;
	int 		path_id;

	path_id = ((t_path *)path->content)->id;
	tunnel = ((t_room *)room->content)->tunnels;
	if (((t_room *)room->content)->end == 1)
		((t_path *)path->content)->complete = true;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == -1)
		{
			((t_path *)path->content)->len++;
			next_room = ((t_tunnel *)tunnel->content)->room;
			((t_room *)room->content)->new_next = next_room;
			((t_room *)room->content)->new_path_id = path_id;
			complete_path(path, next_room);
			return ;
		}
		tunnel = tunnel->next;
	}
}

static int 					sort_by_len(void *a, void *b)
{
	t_path 		*path1;
	t_path 		*path2;

	path1 = (t_path *)a;
	path2 = (t_path *)b;
	return (path1->len < path2->len);
}

static void				complete_paths(t_list **path)
{
	t_list	*room;
	t_list 	*elem;

	elem = *path;
	while (elem)
	{
		room = ((t_path *)elem->content)->room;
		complete_path(elem, room);
		elem = elem->next;
	}
	ft_lst_mergesort(path, sort_by_len);
	elem = *path;
}

static t_list 		*get_longest_path(t_list *path, int ant_qty)
{
	t_list	*head;
	int 		ant_qty_out;
	int 		path_len;

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

static void 			increment_sent_values(t_list *path)
{
	while (path)
	{
		((t_path *)path->content)->sent++;
		path = path->next;
	}
}

static int 				test_solution(t_list *paths, int ant_qty)
{
	t_list	*used_path;
	int 		rounds;

	rounds = 0;
	used_path = paths;
	while (ant_qty > 0)
	{
		used_path = get_longest_path(used_path, ant_qty);
		increment_sent_values(used_path);
		ant_qty -= ft_lstcount(used_path);
		//ft_printf("nb of paths used = %d, ant_qty = %d\n", ft_lstcount(used_path), ant_qty);
		rounds++;
	}
	rounds += ((t_path *)used_path->content)->len - 1;
	//del_paths ?
	return (rounds);
}

static void update_data(t_anthill *anthill, int rounds)
{
	t_list	*room;

	room = anthill->rooms;
	while (room)
	{
		((t_room *)room->content)->next = ((t_room *)room->content)->new_next;
		((t_room *)room->content)->path_id = ((t_room *)room->content)->new_path_id;
		((t_room *)room->content)->previous = NULL;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->dead_end = false;
		((t_room *)room->content)->new_next = NULL;
		((t_room *)room->content)->new_path_id = 0;
		room = room->next;
	}
	anthill->rounds = rounds;
}

static int				min_rounds(t_anthill *anthill, t_list *start
									, t_list *end, t_list **paths)
{
	int			ret;
	t_list	*queue;
	t_list	*previous_paths;

	queue = NULL;
	while (bfs(start, end, &queue))
	{
		previous_paths = *paths;
		*paths = NULL;
		ft_lstdel(&queue, del_steps);
		set_tunnels_usage(end); // set a -1, 0 ou 1 les tunnels->usage de end a start en passant par les previous
		if (!init_paths(paths, start))
			return (0);
		complete_paths(paths);
		ret = test_solution(*paths, anthill->ant_qty); //on teste le nb de lignes
	//	ft_printf("solution tested: %d rounds\n", ret);
		if (ret > anthill->rounds || ret == 0) // et on compare a la solution precedente
		{
			ft_lstdel(paths, del_steps);
			*paths = previous_paths;
			break ;
		}
		update_data(anthill, ret); // maj des pointeurs next et path_id + valeur anthill->rounds
		ft_lstdel(&previous_paths, del_steps);
	}
	return (anthill->rounds != INT_MAX);
}

int						find_paths(t_anthill *anthill, t_list **paths)
{
	if (!min_rounds(anthill, anthill->start, anthill->end, paths))
		return (0);
	return (1);
}
