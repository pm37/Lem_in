/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/21 16:13:47 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

static void		init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->start = NULL;
	anthill->end = NULL;
	anthill->room_qty = 0;
	anthill->rounds = INT_MAX;
	anthill->id = 0;
}

int				main(void)
{
	t_anthill	anthill;
	t_list		*paths;

	paths = NULL;
	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR")); // free everything
	if (!(find_paths(&anthill, anthill.start, anthill.end, &paths)))
		return (0);
	//print_paths(paths);
	ft_lstrev(&paths);
	init_ants(&anthill);
	print_output(&anthill, paths);
	//ft_putnbrendl(anthill.rounds);
	return (0);
}
