/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:28:21 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/02 12:51:16 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

static int		init_ant_qty(char *line, t_anthill *anthill)
{
	if (ft_isinteger(line))
	{
		anthill->ant_qty = ft_atoull(line);
		return (anthill->ant_qty > 0);
	}
	return (0);
}

static int		end_of_rooms(char *line)
{
	if (line[0] == '#')
		return (0);
	if (ft_strchr(line, '-'))
		return (1);
	return (0);
}

static void		init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->start = NULL;
	anthill->end = NULL;
	anthill->room_qty = 0;
	anthill->rounds = LONG_MAX;
	anthill->id = 0;
	anthill->option = 0;
}

static int		create_tunnels(t_anthill *anthill, t_list *input)
{
	if (!input || !add_tunnel(anthill, ((t_input *)input->content)->line))
		return (0);
	input = input->next;
	while (input)
	{
		if (is_a_comment(((t_input *)input->content)->line))
		{
			input = input->next;
			continue ;
		}
		if (!add_tunnel(anthill, ((t_input *)input->content)->line))
			return (0);
		input = input->next;
	}
	return (1);
}

int				create_anthill(t_anthill *anthill, t_list *input)
{
	init_anthill(anthill);
	while (input && is_a_comment(((t_input *)input->content)->line))
		input = input->next;
	if (!init_ant_qty(((t_input *)input->content)->line, anthill))
		return (0);
	input = input->next;
	while (input && !end_of_rooms(((t_input *)input->content)->line))
	{
		if (!add_room(anthill, &input))
			return (0);
		input = input->next;
	}
	if (!anthill->start || !anthill->end)
		return (0);
	return (create_tunnels(anthill, input));
}
