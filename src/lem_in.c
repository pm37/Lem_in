/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/12 16:28:39 by bwan-nan         ###   ########.fr       */
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
	anthill->max_flow = 0;
	anthill->residual_capacity = 0;
	anthill->visited = 2;
}

int				main(void)
{
	t_anthill	anthill;

	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR")); // free everything
	ft_printf("max_flow = %d\n", anthill.max_flow);
	if (!(find_paths(&anthill)))
		return (0);
	return (0);
}
