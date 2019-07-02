/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:53:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/02 11:53:21 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_ant(int id, t_anthill *anthill)
{
	t_ant	ant;
	t_list	*new_ant;

	ant.id = id;
	ant.position = anthill->start->content;
	if (!(new_ant = ft_lstnew(&ant, sizeof(t_ant))))
		return (0);
	ft_lstprepend(&anthill->ants, new_ant);
	return (1);
}
