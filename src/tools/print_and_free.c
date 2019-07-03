/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:30:04 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/03 13:24:54 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_input(t_list **input, char *exit_msg)
{
	ft_lstdel(input, del_input);
	if (exit_msg)
		ft_putendl(exit_msg);
	return (exit_msg ? -1 : 0);
}

int			print_and_free(t_anthill *anthill, t_list **input
			, t_list **paths, char *msg)
{
	if (anthill->rooms)
		ft_lstdel(&anthill->rooms, del_room);
	if (anthill->ants)
		ft_lstdel(&anthill->ants, del_steps);
	ft_lstdel(paths, del_steps);
	return (free_input(input, msg));
}
