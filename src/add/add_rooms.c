/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:44:36 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/18 11:40:55 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_checker(t_anthill *anthill, char **tab)
{
	t_list	*elem;
	t_room	*tmp;

	if (tab[0] && tab[1] && tab[2] && !tab[3])
	{
		if (!ft_isinteger(tab[1]) || !ft_isinteger(tab[2]))
			return (0);
	}
	else
		return (0);
	elem = anthill->rooms;
	while (elem)
	{
		tmp = (t_room *)elem->content;
		if (ft_strequ(tmp->name, tab[0])
		|| (ft_atoi(tab[1]) == tmp->x && ft_atoi(tab[2]) == tmp->y))
			return (0);
		elem = elem->next;
	}
	return (1);
}

static int		set_both_ends(t_room *room, char **line)
{
	static int		end = 0;
	int				a;
	int				b;

	a = 0;
	b = 0;
	if ((a = ft_strequ(*line, "##start")) && (end == 1 || end == 3))
		return (0);
	else if ((b = ft_strequ(*line, "##end")) && end >= 2)
		return (0);
	get_next_line(0, line);
	if (*line == NULL)
		return (0);
	if (a)
	{
		room->end = 0;
		end++;
	}
	else if (b)
	{
		room->end = 1;
		end += 2;
	}
	return (1);
}

static void		init_pointer_to_end(t_anthill *anthill, t_list *ptr, int end)
{
	if (end == 0)
		anthill->start = ptr;
	else
		anthill->end = ptr;
}

static int		init_room(t_anthill *anthill, t_room *room, char **tab)
{
	if (!(room->name = ft_strdup(tab[0])))
		return (0);
	room->x = ft_atoi(tab[1]);
	room->y = ft_atoi(tab[2]);
	room->path_id = 0;
	room->tunnels = NULL;
	room->next = NULL;
	room->previous = NULL;
	room->new_next = NULL;
	room->visited = false;
	room->deviation = false;
	room->path_id = 0;
	room->new_path_id = 0;
	room->dead_end = false;
	(anthill->room_qty)++;
	return (1);
}

int				add_room(t_anthill *anthill, char *line)
{
	char			**tab;
	t_room			room;
	t_list			*new;

	if (line[0] == 'L')
		return (0);
	room.end = -1;
	if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
	{
		if (!set_both_ends(&room, &line))
			return (0);
	}
	else if (line[0] == '#')
		return (1);
	tab = ft_strsplit(line, ' ');
	if (!init_room(anthill, &room, tab) || !room_checker(anthill, tab)
	|| !(new = ft_lstnew(&room, sizeof(t_room))))
		return (ret_freetab(0, tab));
	if (room.end != -1)
		init_pointer_to_end(anthill, new, room.end);
	ft_lstappend(&anthill->rooms, new);
	return (1);
}
