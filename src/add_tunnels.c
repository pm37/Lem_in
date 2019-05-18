/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/18 12:54:03 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_tunnel(char **tunnel, t_anthill *anthill)
{
	if (!tunnel[0] || !tunnel[1] || tunnel[2])
		return (0);
}

static int	create_tunnel(t_list *room1, t_list *room2)
{

}

int			add_tunnel(char *line, t_anthill *anthill)
{
	char	**tunnel;
	t_list	*room1;
	t_list	*room2;

	if (!(tunnel = ft_strsplit(line, '-')))
		return (0);
	if (!check_tunnel(tunnel, room1, room2, anthill))
		return (ret_freetab(0, tunnel));
	create_tunnel(room1, room2);
}
