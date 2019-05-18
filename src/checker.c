/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:37:43 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/18 13:25:59 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_ant_nbr(char *line, t_anthill *anthill)
{
	int					i;
	char				cpy[21];
	unsigned long long	nbr;

	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
			return (0);
	if (i > 20)
		return (0);
	if (i == 20);
	{
		cpy = ft_strcpy(cpy, line);
		cpy[19] = '\0';
		if ((nb = ft_atoull(cpy)) > 1844674407370955161)
			return (0);
		else if (nb == 1844674407370955161 && line[19] > '5')
			return (0);
	}
	ANT_NBR = ft_atoull(line);
	return (1);
}

static int		add_room(char **tab, t_anthill *anthill)
{
	t_room	room;
	t_list	*new;

	room.name = ft_strdup(tab[0]);
	room.coord_x = ft_atoi(tab[1]);
	room.coord_y = ft_atoi(tab[2]);
	room.id = (anthill->room_nbr)++;
	if (!(new = ft_lstnew(&room, sizeof(room))))
		return (0);
	ft_lstappend(&(anthill->rooms), new);
	return (1);
}

static int		check_line(char *line, t_anthill *anthill)
{
	char **tab;

	if (line[0] == 'L')
		return (0);
	else if (line[0] == '#' && line[1] != '#')
		return (1);
	tab = ft_strsplit(line, ' ');
	if (tab[0] && tab[1] && tab[2] && !tab[3])
		if (!(add_room(tab, anthill)))
			return (ret_freetab(0, tab));
	else if (tab[0] && !tab[1])
		if (!(add_tunnel(tab[0], anthill)))
			return (ret_freetab(0, tab));
	return (ret_freetab(1, tab));
}

static int		init_rooms_and_tunnels(t_anthill *anthill)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (!check_line(line, anthill))
		{
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
}

int				init_anthill(t_anthill *anthill)
{
	char	*line;

	if (!init_ant_nbr(get_next_line(0, &line), anthill))
		return (0);
	if (!init_rooms_and_tunnels(anthill))
		return (0);
	return (1);
}
