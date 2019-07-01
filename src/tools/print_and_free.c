/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:30:04 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/01 16:35:04 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_input(t_list **input, int exit_value)
{
	ft_lstdel(input, del_input);
	return (exit_value);
}

int			print_and_free(t_anthill *anthill, t_list **input
			, t_list **paths, char *msg)
{
	if (anthill->rooms)
		ft_lstdel(&anthill->rooms, del_room);
	if (anthill->ants)
		ft_lstdel(&anthill->ants, del_steps);
	ft_lstdel(paths, del_steps);
	if (msg)
		ft_putendl(msg);
	return (free_input(input, msg == NULL ? 0 : -1));
}
