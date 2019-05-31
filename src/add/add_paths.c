/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:15:45 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/31 18:32:39 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_step(t_list **steps, t_list *room)
{
	t_list	*new_step;

	if (!(new_step = ft_lstnew(new_step, sizeof(t_list))))
		return (0);
	new_step->content = (void *)room;
	((t_room *)room->content)->visited = true;
	ft_lstprepend(steps, new_step);
	return (1);
}

static int		duplicate_path(t_anthill *anthill, t_list *target)
{
	t_list	*path;
	t_list	*duplicate;

	path = anthill->paths;
	while (path)
	{
		if (path == target)
		{
			if (!(duplicate = ft_lstcpy(path, copy_path)))
				return (0);
			ft_lstprepend(&anthill->paths, duplicate);
		}
		path = path->next;
	}
	print_paths(anthill->paths);
	return (1);
}


int		add_path(t_anthill *anthill, t_list *target, t_list *room)
{
	t_list	*steps;

	if (!(duplicate_path(anthill, target)))
		return (0);
	steps = ((t_path *)(anthill->paths->content))->steps;
	steps->content = (void *)room;
	return (1);
}
