/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/05 16:42:05 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->paths = NULL;
	anthill->start = NULL;
	anthill->end = NULL;
	anthill->good_paths = NULL;
	anthill->room_qty = 0;
	anthill->visited = 2;
}

int				main(void)
{
	t_anthill	anthill;

	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR")); // free everything

	if (!(find_paths(&anthill)))
		return (0);
//	ft_printf("start name = %s\n", ((t_room *)(anthill.start->content))->name);
//	ft_printf("end name = %s\n", ((t_room *)(anthill.end->content))->name);
	return (0);
}
