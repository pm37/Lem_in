/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/21 15:25:29 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	create_tunnel(t_list *room1, t_list *room2)
{
	
	return (1);
}

static int	tunnel_checker(char **tunnel, t_anthill *anthill)
{
	t_list	*elem;
	t_list	*room1;
	t_list	*room2;
	int		check;

	check = 0;
	if (tunnel[0][0] == '#')
		return (1);
	if (!tunnel[0] || !tunnel[1] || tunnel[2])
		return (0);
	elem = anthill->rooms;
	while (elem && check < 2)
	{
		if (ft_strequ(tunnel[0], elem.name) && ++check)
			room1 = elem;
		if (ft_strequ(tunnel[1], elem.name) && ++check)
			room2 = elem;
		elem = elem->next;
	}
	if (!elem && check != 2)
		return (0);
	return (create_tunnel(room1, room2));
}

int			add_tunnel(char *line, t_anthill *anthill)
{
	char	**tunnel;

	if (!(tunnel = ft_strsplit(line, '-')))
		return (0);
	if (!tunnel_checker(tunnel, anthill))
		return (ret_freetab(0, tunnel));
	return (ret_freetab(1, tunnel));
}
