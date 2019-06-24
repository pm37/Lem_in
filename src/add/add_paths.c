/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:15:45 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/24 14:55:18 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
static int		duplicate_path(t_anthill *anthill, t_list *target)
{
	t_list	*path;
	t_list	*duplicate;

	path = anthill->paths;
	while (path)
	{
		if (path == target)
		{
			if (!(duplicate = ft_lstncpy(path, 1, copy_path)))
				return (0);
			ft_lstprepend(&anthill->paths, duplicate);
		}
		path = path->next;
	}
	return (1);
}
*/
/*
int				add_step(t_list **steps, t_list *room)
{
	t_list	*new_step;

	if (!(new_step = ft_lstnew(new_step, sizeof(t_list))))
		return (0);
	new_step->content = (void *)room;
	((t_room *)room->content)->visited = true;
//	if (((t_room *)room->content)->end != 1)
//		anthill->visited++;
	ft_lstprepend(steps, new_step);
	return (1);
}
*/
/*
int				add_path(t_anthill *anthill, t_list *target, t_list *room)
{

	if (!(duplicate_path(anthill, target)))
		return (0);
	((t_path *)anthill->paths->content)->steps->content = (void *)room;
	((t_room *)room->content)->visited = true;
	anthill->visited++;
	return (1);
}
*/
/*
int				add_path(t_list **paths)
{
	t_path	path;
	t_list	*new_path;

	path.len = 0;
	path.steps = NULL;
	if (!(new_path = ft_lstnew(&path, sizeof(t_list))))
		return (0);
	ft_lstprepend(paths, new_path);
	return (1);
}

int 			complete_path(t_list **paths, t_list *room)
{

}

*/
