/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:37:43 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/22 20:42:46 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_ant_qty(char *line, t_anthill *anthill)
{
	int					i;
	char				cpy[21];
	unsigned long long	nb;

	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
			return (0);
	if (i > 20)
		return (0);
	if (i == 20)
	{
		ft_strcpy(cpy, line);
		cpy[19] = '\0';
		if ((nb = ft_atoull(cpy)) > 1844674407370955161)
			return (0);
		else if (nb == 1844674407370955161 && line[19] > '5')
			return (0);
	}
	anthill->ant_qty = ft_atoull(line);
	return (1);
}

static int		end_of_rooms(char *line)
{
	if (line[0] == '#')
		return (0);
	if (line[0] == 'L')
		return (1);
	if (ft_strchr(line, '-'))
		return (1);
	return (0);
}

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

static int		add_room(char *line, t_anthill *anthill)
{
	char	**tab;
	t_room	room;
	t_list	*new;

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

int				create_anthill(t_anthill *anthill)
{
	char	*line;

	if (!get_next_line(0, &line) || !init_ant_qty(line, anthill))
		return (0);
	while (get_next_line(0, &line) > 0 && !end_of_rooms(line))
	{
		if (!add_room(line, anthill))
			return (ret_freeline(0, &line));
		ft_strdel(&line);
	}
	if (!add_tunnel(anthill, line))
	{
		ft_putendl("ok");
		return (ret_freeline(0, &line));
	}
	ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		if (!add_tunnel(anthill, line))
			return (ret_freeline(0, &line));
		ft_strdel(&line);
	}
	return (1);
}
