/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:53:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/13 00:21:02 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_path(t_list **paths, t_list *room)
{
  t_list      *new_path;
	t_path	    path;
  static int  path_id = 0;

	path.len = 1;
	path.id = ++path_id;
  path.sent = 0;
  path.used = true;
  path.room = NULL;
  path.complete = false;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (0);
	((t_path *)new_path->content)->room = room;
	ft_lstprepend(paths, new_path);
	return (1);
}

int				init_paths(t_list **paths, t_list *start)
{
	t_list	*room;
	t_list	*tunnel;

	room = start;
	tunnel = ((t_room *)(room->content))->tunnels;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == -1)
		{
			if (!init_path(paths, ((t_tunnel *)tunnel->content)->room))
				return (0);
		}
		tunnel = tunnel->next;
	}
  ft_printf("initialized %d path%s"
  , ft_lstcount(*paths)
  , ft_lstcount(*paths) > 1 ? "s\n" : "\n");
	return (1);
}
