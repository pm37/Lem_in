/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:58:14 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/01 16:58:20 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_ants(t_anthill *anthill)
{
	int		i;

	anthill->ants = NULL;
	i = anthill->ant_qty + 1;
	while (--i)
	{
		if (!add_ant(i, anthill))
			return (0);
	}
	return (1);
}
