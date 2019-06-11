/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:53:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/10 15:23:14 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_path(t_anthill *anthill)
{
	t_list	*new_path;
	t_list	*start;
	t_path	origin;

	origin.len = 1;
	origin.explored = false;
	if (!(origin.steps = ft_lstnew(start, sizeof(t_list))))
			return (0);
	origin.steps->content = (void *)anthill->start;
	if (!(new_path = ft_lstnew(&origin, sizeof(t_path))))
		return (0);
	((t_room *)anthill->start->content)->visited = true;
	ft_lstprepend(&anthill->paths, new_path);
	return (1);
}

int				init_paths(t_anthill *anthill)
{
	t_list	*new_step;
	t_list	*room;
	t_list	*tunnel;

	room = anthill->start;
	tunnel = ((t_room *)(room->content))->tunnels;
	while (tunnel)
	{
		if (!init_path(anthill))
			return (0);
		room = tunnel->content;
		((t_room *)room->content)->visited = true;
		anthill->visited++;
	//	ft_printf("tunnel name = %s\n", ((t_room *)(room->content))->name);
		if (!(new_step = ft_lstnew(new_step, sizeof(t_list))))
			return (0);
		new_step->content = (void *)room;
		ft_lstprepend(&((t_path *)(anthill->paths->content))->steps, new_step);
		tunnel = tunnel->next;
	}
	return (1);
}

