/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:04:51 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/28 12:58:52 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_rooms_content(t_list *room)
{
	while (room)
	{
		ft_strdel(&((t_room *)room->content)->name);
		ft_lstdel(&((t_room *)room->content)->tunnels, del_steps);
		room = room->next;
	}
}

int			ret_print_free_all(t_anthill *ath, t_list **input, t_list **paths,
		char *msg)
{
	if (ath->rooms)
	{
		free_rooms_content(ath->rooms);
		ft_lstdel(&ath->rooms, del_steps);
	}
	ft_lstdel(paths, del_steps);
	if (msg)
		ft_putendl(msg);
	return (ret_free_input(input));
}

int			ret_print(int ret, char *msg)
{
	ft_putendl(msg);
	return (ret);
}
