/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/13 00:46:44 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int 			check_tunnel(t_list *current, t_list *tunnel)
{
	t_list	*ptr;
	t_room	*dest;
	t_room 	*src;

	ptr = tunnel->content;
	src = (t_room *)current->content;
	dest = (t_room *)ptr->content;
	return (dest->visited == true || ptr->usage == -1
	|| (src->deviation == true && ptr->usage == 0));
}

static int 			going_to_deviate(t_list *current, t_list *room)
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
		if ((t_tunnel *)tunnel->content)->usage == 1)
		{
			tunnel_used = 1;
			break ;
		}
		tunnel = tunnel->next;
	}
	return (!src->deviation && tunnel_used && src->path_id != dest->path_id);
}

static int 			complete_queue(t_list *queue)
{
	t_list	*tunnel;
	t_list	*room;
	t_list	*current;

	room = queue;
	current = room;
	tunnel = ((t_room *)room->content)->tunnels;
	while (tunnel)
	{
		if (check_tunnel(current, tunnel) && (tunnel = tunnel->next))
			continue ;
		room = ((t_tunnel *)tunnel->content)->room;
		add_to_queue(queue, room);
		((t_room *)room->content)->previous = current;
		((t_room *)room->content)->visited = true;
		if (going_to_deviate(current, room))
			((t_room *)room->content)->deviation = true;
		tunnel = tunnel->next;
	}
}

static int			init_queue(t_list **queue, t_list **head, t_list *start)
{
	t_list	new;

	if (!(*queue = ft_lstnew(&new, sizeof(t_list))))
		return (0);
	(*queue)->content = (void *)start;
	*head = *queue;
	return (1);
}

static bool			bfs(t_anthill *anthill, t_list *start, t_list *end)
{
	t_list		*queue;
	t_list		*head;
	bool 			found_augmented_path;

	found_augmented_path = false;
	if (!init_queue(&queue, &head, start))
		return (0);
	while (queue)
	{
		if (!complete_queue(queue))
			return (0);				// regarde les tunnels du top de la liste queue
												// et les ajoute a la queue
												// et set les previous
												// et set les visited
		if (((t_room *)end->content)->visited)
		{
			found_augmented_path = true;
			break ;
		}
		queue = queue->next;
	}
	ft_lstdel(&head, del_steps);
	return (found_augmented_path);
}

static t_list			*get_tunnel(t_list *src, t_list *dest)
{
	t_list	*tunnel;
	t_list	*room;

	tunnel = ((t_room *)src->content)->tunnels;
	while (tunnel)
	{
		room = tunnel->content;
		if (room == dest)
			return (tunnel);
		tunnel = tunnel->next;
	}
	return (NULL);
}

static void set_usage(t_list *src, t_list *dest, bool is_previous)
{
	t_list	*tunnel;

	tunnel = get_tunnel(src, dest);
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

	tunnel = ((t_room *)room->content)->tunnels;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == -1)
		{
			path->len++;
			next_room = ((t_tunnel *)tunnel->content)->room;
			((t_room *)room->content)->new_next = next_room;
			complete_path(path, ptr);
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

static void 				complete_paths(t_list *path)
{
	t_list	*room;

	while (path)
	{
		room = ((t_path *)path->content)->room;
		complete_path(path, room);
		path = path->next;
	}
	ft_lst_mergesort(&path, sort_by_len);
}

static void 			get_longest_path(&path, ant_qty)
{

}

static int 				test_solution(t_list *paths, int ant_qty)
{
	t_list	*first_used_path;
	int 		longest;

	first_used_path = paths;
	while (ant_qty > 0)
	{
		get_longest_path(&first_used_path, ant_qty);
		ant_qty -= ft_lstcount(first_used_path);
	}
	//del_paths
}

static int				min_rounds(t_anthill *anthill, t_list *start, t_list *end)
{
	int			ret;
	t_list	*paths;

	max_flow = 0;
	while (bfs(anthill, start, end))
	{
		set_tunnels_usage(end); // set a -1, 0 ou 1 les tunnels->usage de end a start en passant par les previous
		if (!init_paths(&paths, start) || !complete_paths(paths))
			return (0);
		ret = test_solution(paths, anthill->ant_qty); //on teste le nb de lignes
		if (ret >= anthill->rounds || ret == 0) // et on compare a la solution precedente
			break ;
		update_paths(start); // maj des pointeurs next et path_id
		reset_rooms(anthill->rooms); //reset visited, previous et deviation
		anthill->rounds = ret;
	}
	return (anthill->rounds != INT_MAX);
}

int						find_paths(t_anthill *anthill)
{
	if (!min_rounds(anthill, anthill->start, anthill->end))
		return (0);
	return (1);
}
