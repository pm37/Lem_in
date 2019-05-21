/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/21 18:50:35 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	tunnel_exists(t_list *origin, t_list *dest)
{
	t_list	*elem;

	elem = origin;
	while (elem)
	{
		if (elem->content == dest)
			return (1);
		elem = elem->next;
	}
	return (0);
}

static int	create_tunnel(t_list *room1, t_list *room2)
{
	t_list	*new;
	t_list	cpy;
	t_room	*tmp;

	tmp = (t_room *)(room1->content);
	if (tunnel_exists(tmp->tunnels, room2))
		return (0);
	if (!(new = ft_lstnew(&cpy, sizeof(t_list))))
		return (0);
	new->content = (void *)room2;
	ft_lstappend(&tmp->tunnels, new);
	return (1);
}

static int	tunnel_checker(t_anthill *anthill, char **tunnel)
{
	t_list	*elem;
	t_list	*room1;
	t_list	*room2;
	t_room	*tmp;
	int		check;

	check = 0;
	if (tunnel[0][0] == '#')
		return (1);
	if (!tunnel[0] || !tunnel[1] || tunnel[2])
		return (0);
	elem = anthill->rooms;
	while (elem && check < 2)
	{
		tmp = (t_room *)elem->content;
		if (ft_strequ(tunnel[0], tmp->name) && ++check)
			room1 = elem;
		if (ft_strequ(tunnel[1], tmp->name) && ++check)
			room2 = elem;
		elem = elem->next;
	}
	if (!elem && check != 2)
		return (0);
	return (create_tunnel(room1, room2) && create_tunnel(room2, room1));
}

int			add_tunnel(t_anthill *anthill, char *line)
{
	char	**tunnel;

	if (!(tunnel = ft_strsplit(line, '-')))
		return (0);
	if (!tunnel_checker(anthill, tunnel))
		return (ret_freetab(0, tunnel));
	ft_putendl("OK");
	return (ret_freetab(1, tunnel));
}
