/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/18 13:25:56 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	set_room(char *name, t_list **room, t_anthill *anthill)
{
	t_list	*elem;

	elem = anthill->rooms;
	while (elem)
	{
		if (ft_strequ(elem.name, name))
		{
			*room = elem;
			return (1);
		}
		elem = elem->next;
	}
	return (0);
}

static int	check_tunnel(char **tunnel, t_list **room1, t_list **room2,
			t_anthill *anthill)
{
	if (!tunnel[0] || !tunnel[1] || tunnel[2]
	|| !set_room(tunnel[0], room1, anthill) 
	|| !set_room(tunnel[1], room2, anthill))
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
	if (!check_tunnel(tunnel, &room1, &room2, anthill))
		return (ret_freetab(0, tunnel));
	create_tunnel(room1, room2);
	return (ret_freetab(1, tunnel));
}
