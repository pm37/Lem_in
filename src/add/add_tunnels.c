/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/12 23:46:54 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	tunnel_exists(t_list *origin, t_list *dest)
{
	t_list	*elem;

	elem = origin;
	while (elem)
	{
		if (((t_tunnel *)elem->content)->room == dest)
			return (1);
		elem = elem->next;
	}
	return (0);
}

static int	rooms_exist(t_list *head, t_list **room1,
			t_list **room2, char **rooms)
{
	t_list	*elem;
	t_room	*tmp;
	int		check;

	check = 0;
	elem = head;
	while (elem && check < 2)
	{
		tmp = (t_room *)elem->content;
		if (ft_strequ(rooms[0], tmp->name) && ++check)
			*room1 = elem;
		if (ft_strequ(rooms[1], tmp->name) && ++check)
			*room2 = elem;
		elem = elem->next;
	}
	return (check == 2);
}

static int	create_tunnel(t_list *room1, t_list *room2)
{
	t_list		*new_tunnel;
	t_tunnel	tunnel;
	t_room		*origin;

	origin = (t_room *)(room1->content);
	tunnel.capacity = 1;
	tunnel.room = NULL;
	if (tunnel_exists(origin->tunnels, room2))
		return (0);
	if (!(new_tunnel = ft_lstnew(&tunnel, sizeof(t_list))))
		return (0);
	((t_tunnel *)new_tunnel->content)->room = room2;
	ft_lstappend(&origin->tunnels, new_tunnel);
	return (1);
}

static int	tunnel_checker(t_anthill *anthill, char **rooms)
{
	t_list	*head;
	t_list	*room1;
	t_list	*room2;

	room1 = NULL;
	room2 = NULL;
	if (rooms[0][0] == '#')
		return (1);
	head = anthill->rooms;
	if (!rooms[0] || !rooms[1] || rooms[2]
	|| !rooms_exist(head, &room1, &room2, rooms))
		return (0);
	return (create_tunnel(room1, room2) && create_tunnel(room2, room1));
}

int			add_tunnel(t_anthill *anthill, char *line)
{
	char	**rooms;

	rooms = NULL;
	if (line[0] == '#')
		return (1);
	if (count_occurence(line, '-') != 1 || !(rooms = ft_strsplit(line, '-')))
		return (0);
	if (!tunnel_checker(anthill, rooms))
		return (ret_freetab(0, rooms));
	return (ret_freetab(1, rooms));
}
