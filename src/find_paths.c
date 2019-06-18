/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/18 14:05:38 by bwan-nan         ###   ########.fr       */
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
	//ft_printf("dev name = %s\n", ((t_room *)deviation_room->content)->name);
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
	if (((t_room *)prev_room->content)->visited == false)
	{
		((t_room *)deviation_room->content)->visited = true;
		((t_room *)prev_room->content)->visited = true;
		ret = bfs(prev_room, end, &queue);
		reset_visited_rooms(deviation_room, prev_room, queue, end);
		ft_lstdel(&queue, del_steps);
	}
	return (ret);
}

static int 			check_tunnel(t_list *current, t_list *tunnel, t_list *end)
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
	//	ft_printf("curr vers dev = %s\n", ((t_room *)current->content)->name);
		return (!deviation_reaches_end(room, end));
	}
	return (dest->visited == true
	|| usage == -1
	|| dest->end == 0
	|| (src->deviation && usage == 0));
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
/*	ft_printf("from %s, path_id = %d, visited = %d | to add = %s, path_id = %d, visited = %d\n"
	, ((t_room *)from->content)->name
	, ((t_room *)from->content)->path_id
	, ((t_room *)from->content)->visited == true
	, ((t_room *)room->content)->name
	, ((t_room *)room->content)->path_id
	, ((t_room *)room->content)->visited == true);*/
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
//	((t_room *)current->content)->visited = true;
	tunnel = ((t_room *)current->content)->tunnels;
	while (tunnel)
	{
		room = ((t_tunnel *)tunnel->content)->room;
		if (check_tunnel(current, tunnel, end))
		{
			tunnel = tunnel->next;
			continue ;
		}
		if (!add_to_queue(&queue, room))
			return (0);
		((t_room *)room->content)->previous = current;
		((t_room *)room->content)->visited = true;
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

static void 	print_queue(t_list *queue)
{
	t_list	*room;
	while (queue)
	{
		room = queue->content;
	//	ft_printf("%s%c", ((t_room *)room->content)->name, queue->next ? '-' : '\n');
		queue = queue->next;
	}
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
	//	ft_printf("\nqueue elem : %s\n",
	//	(((t_room *)room->content)->name));
		if (!complete_queue(*queue, end))
			return (false);
		print_queue(*queue);
		if (((t_room *)end->content)->visited)
		{
			found_augmented_path = true;
			break ;
		}
		*queue = (*queue)->next;
	}
	*queue = head;
	//ft_lstdel(&head, del_steps);
//	ft_printf("return %d\n", found_augmented_path == true);
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

static void				complete_paths(t_list *path)
{
	t_list	*room;
	//t_list	*head;

	//head = path;
	while (path)
	{
		room = ((t_path *)path->content)->room;
		complete_path(path, room);
		path = path->next;
	}
	/*path = head;
	while (path)
	{
		room = ((t_path *)path->content)->room;
		print_steps(room);
		if (((t_path *)path->content)->complete == false)
			ft_lstpop(&head, path, del_steps);
		else
			ft_putendl("true");
		path = path->next;
	}*/
	ft_lst_mergesort(&path, sort_by_len);
}

static t_list 		*get_longest_path(t_list *path, int ant_qty)
{
	t_list	*head;
	int 		ant_qty_out;
	int 		path_len;

	if (!path)
		return (NULL);
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

static int 				test_solution(t_list *paths, int ant_qty)
{
	t_list	*used_path;
	int 		rounds;

	rounds = 0;
	used_path = paths;
	while (ant_qty > 0)
	{
		//ft_printf("entry with %d ants left\n", ant_qty);
		if (!(used_path = get_longest_path(used_path, ant_qty)))
			return (0);
		//	ft_printf("used_path id = %d\n", ((t_path *)used_path->content)->id);
	//	ft_putendl("out");
	//	ft_printf("lst count = %d\n", ft_lstcount(used_path));
		ant_qty -= ft_lstcount(used_path);
		rounds++;
	}
	//del_paths ?
	return (rounds);
}

static void update_rooms(t_list *room)
{
	while (room)
	{
		((t_room *)room->content)->next = ((t_room *)room->content)->new_next;
		((t_room *)room->content)->path_id = ((t_room *)room->content)->new_path_id;
		((t_room *)room->content)->previous = NULL;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->new_next = NULL;
		((t_room *)room->content)->new_path_id = 0;
		room = room->next;
	}
}
/*
static void			debug(t_list *room)
{

	t_list	*next_room;

	while (room)
	{
		next_room = ((t_room *)room->content)->next;
		ft_printf("Name = %s, visited = %d, devi = %d, path_id = %d, next->name = %s, new_path_id = %d, new_next = %p\n"
		, ((t_room *)room->content)->name
		, ((t_room *)room->content)->visited == true
		, ((t_room *)room->content)->deviation == true
		, ((t_room *)room->content)->path_id
		, next_room ? ((t_room *)next_room->content)->name : "NULL"
		, ((t_room *)room->content)->new_path_id
		, ((t_room *)room->content)->new_next);
		room = room->next;
	}
}

static void			print_usage(t_list *room)
{
	t_list	*tunnel;
	t_list	*dest_room;

	while (room)
	{
		tunnel = ((t_room *)room->content)->tunnels;
		while (tunnel)
		{
			dest_room = ((t_tunnel *)tunnel->content)->room;
			ft_printf("room = %s, dest = %s, usage = %d\n"
			, ((t_room *)room->content)->name
			, ((t_room *)dest_room->content)->name
			, ((t_tunnel *)tunnel->content)->usage);
			tunnel = tunnel->next;
		}
		room = room->next;
	}
}

*/
static int				min_rounds(t_anthill *anthill, t_list *start, t_list *end)
{
	int			ret;
	t_list	*paths;
	t_list	*queue;

	paths = NULL;
	queue = NULL;
	while (bfs(start, end, &queue))
	{
		ft_lstdel(&queue, del_steps);
		set_tunnels_usage(end); // set a -1, 0 ou 1 les tunnels->usage de end a start en passant par les previous
		//ft_putendl("usage set");
		if (!init_paths(&paths, start))
			return (0);
	//	ft_putendl("paths init");
		complete_paths(paths);
	//	ft_putendl("paths completed");
	print_paths(anthill->start);
		ret = test_solution(paths, anthill->ant_qty); //on teste le nb de lignes
		ft_printf("solution tested: %d rounds\n", ret);
//		if (ret >= anthill->rounds || ret == 0) // et on compare a la solution precedente
	//		break ;
		update_rooms(anthill->rooms); // maj des pointeurs next et path_id
		//reset_rooms(anthill->rooms); //reset visited, previous et deviation
		anthill->rounds = ret;
	//	print_usage(anthill->start);
	//	debug(anthill->rooms);
		ft_putendl("\n\n");
		ft_lstdel(&paths, del_steps);
	}
	return (anthill->rounds != INT_MAX);
}

int						find_paths(t_anthill *anthill)
{
	if (!min_rounds(anthill, anthill->start, anthill->end))
		return (0);
	return (1);
}
