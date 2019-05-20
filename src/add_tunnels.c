/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/20 17:18:15 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	tunnel_checker(char **tunnel, t_list **room1, t_list **room2,
			t_anthill *anthill)
{
	t_list	*elem;
	int		check;

	check = 0;
	if (!tunnel[0] || !tunnel[1] || tunnel[2])
		return (0);
	elem = anthill->rooms;
	while (elem && check < 2)
	{
		if (ft_strequ(tunnel[0], elem.name) && ++check)
			*room1 = elem;
		if (ft_strequ(tunnel[1], elem.name) && ++check)
			*room2 = elem;
		elem = elem->next;
	}
	if (!elem && check != 2)
		return (0);
	return (1);
}

static int	create_tunnel(t_list *room1, t_list *room2)
{
	return (1);
}

int			add_tunnel(char *line, t_anthill *anthill)
{
	char	**tunnel;
	t_list	*room1;
	t_list	*room2;

	if (!(tunnel = ft_strsplit(line, '-')))
		return (0);
	if (!tunnel_checker(tunnel, &room1, &room2, anthill))
		return (ret_freetab(0, tunnel));
	create_tunnel(room1, room2);
	return (ret_freetab(1, tunnel));
}
