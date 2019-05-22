/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:44:36 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/22 12:55:50 by bwan-nan         ###   ########.fr       */
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

int				end_of_rooms(char *line)
{
	if (line[0] == '#')
		return (0);
	if (ft_strchr(line, '-'))
		return (1);
	return (0);
}

int				add_room(t_anthill *anthill, char *line)
{
	char	**tab;
	t_room	room;
	t_list	*new;

	if (line[0] == 'L')
		return (0);
	if (line[0] == '#')
		return (1);
	tab = ft_strsplit(line, ' ');
	if (!room_checker(anthill, tab))
		return (ret_freetab(0, tab));
	room.name = ft_strdup(tab[0]);
	room.x = ft_atoi(tab[1]);
	room.y = ft_atoi(tab[2]);
	room.id = (anthill->room_qty)++;
	room.tunnels = NULL;
	if (!(new = ft_lstnew(&room, sizeof(t_room))))
		return (0);
	ft_lstappend(&anthill->rooms, new);
	return (1);
}

