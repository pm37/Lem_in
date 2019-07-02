/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 19:12:54 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/02 12:53:24 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_steps(void *content, size_t size)
{
	if (content && size)
		free(content);
}

void		del_room(void *content, size_t size)
{
	t_room	*room;

	room = (t_room *)content;
	if (content && size)
	{
		ft_strdel(&room->name);
		ft_lstdel(&room->tunnels, del_steps);
		free(content);
	}
}

void		del_input(void *content, size_t size)
{
	t_input		*input;

	input = (t_input *)content;
	if (content && size)
	{
		ft_strdel(&input->line);
		free(content);
	}
}

void		del_queue_elem(void *content, size_t size)
{
	if (content && size)
		;
}

void		del_lists(t_list **a, t_list **b)
{
	ft_lstdel(a, del_steps);
	ft_lstdel(b, del_steps);
}
