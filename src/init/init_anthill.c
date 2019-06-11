/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:28:21 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/11 14:38:10 by bwan-nan         ###   ########.fr       */
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
	if (ft_strchr(line, '-'))
		return (1);
	return (0);
}

static int		get_min(int a, int b, int c)
{
	int	min;

	if (a < b)
	{
		min = a;
		if (c < a)
			min = c;
	}
	else
	{
		min = b;
		if (c < b)
			min = c;
	}
	return (min);
}

static int		count_links(t_list *room)
{
	t_list	*tunnels;

	tunnels = ((t_room *)room->content)->tunnels;
	return (ft_lstcount(tunnels));
}

int				create_anthill(t_anthill *anthill)
{
	char	*line;

	//La 1ere ligne pourrait etre un commentaire
	if (!get_next_line(0, &line) || !init_ant_qty(line, anthill))
		return (0);
	while (get_next_line(0, &line) > 0 && !end_of_rooms(line))
	{
		if (!add_room(anthill, line))
			return (ret_freeline(0, &line)); // && ret_freeanthill();
		ft_strdel(&line);
	}
	if (!add_tunnel(anthill, line))
		return (ret_freeline(0, &line));
	ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		if (!add_tunnel(anthill, line))
			return (ret_freeline(0, &line));
		ft_strdel(&line);
	}
	anthill->max_flow = get_min(anthill->ant_qty
	, count_links(anthill->start), count_links(anthill->end));
	return (1);
}
