/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/23 17:59:16 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->paths = NULL;
	anthill->start = NULL;
	anthill->end = NULL;
	anthill->room_qty = 0;
}

static void	print_paths(t_list *paths)
{
	t_list *elem;

	elem = paths;
	while (elem)
	{
		ft_printf("path : %s\n", ((t_path *)(elem->content))->path);
		elem = elem->next;
	}
}

int			main(void)
{
	t_anthill	anthill;

	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR")); // free everything
	ft_printf("start name = %s\n", ((t_room *)(anthill.start->content))->name);
	ft_printf("end name = %s\n", ((t_room *)(anthill.end->content))->name);
	if (!find_paths(&anthill, anthill.end,
	((t_room *)(anthill.end->content))->name))
		return (0); //free everything
	print_paths(anthill.paths);
	return (0);
}
