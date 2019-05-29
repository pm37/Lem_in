/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_with_bfs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:52:59 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/29 19:13:50 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			init_paths(t_anthill *anthill)
{
	t_list	*new_path;
	t_path	new_path_content;

	new_path_content.len = 0;
	new_path_content.finished = 0;
	new_path_content.steps = anthill->start;
	new_path_content.id = anthill->path_ids++;
	if (!(new_path = ft_lstnew(&new_path_content, sizeof(t_path))))
		return (0);
	ft_lstappend(&anthill->paths, new_path);
	((t_room *)anthill->start->content)->visited = 1;
	return (1);
}

static int	add_step(t_list *path, t_list *tunnel)
{
	t_list	*new_step;

	if (!(new_step = ft_lstnew(new_step, sizeof(t_list))))
		return (0);
	new_step->content = (void *)tunnel;
	ft_lstprepend(&(((t_path *)path->content)->steps), new_step);
	ft_printf("est passe par add_step\n");
	return (1);
}

static int	check_tunnel(t_anthill *anthill, t_list *path, t_list *tunnel)
{
	(void)anthill;
	if (((t_room *)tunnel->content)->visited)
	{
		if (((t_room *)tunnel->content)->visited_by == ((t_path *)path->content)->id)
			return (0);
		((t_path *)path->content)->finished = 1;
	}
	return (1);
}

static int	copy_path(void *dest, void *src)
{
	ft_memcpy(dest, src, sizeof(void *));
	return (1);
}

static int	copy_node(void *dest, void *src)
{
	ft_memcpy(dest, src, sizeof(t_path));
	return (1);
}

static int	complete_path(t_anthill *anthill, t_list *path)
{
	t_list	*tunnel;
	t_list	*room;
	t_list	*cpy;
	t_list	*cpy2;
	int		i;

	i = 0;
	room = ((t_path *)path->content)->steps;
	tunnel = ((t_room *)room->content)->tunnels;
	while (tunnel && ++i)
	{
		ft_printf("tunnel\n");
		if (i == 1 && check_tunnel(anthill, path, tunnel))
			add_step(path, tunnel);
		else if (check_tunnel(anthill, path, tunnel))
		{
			cpy2 = ft_lstncpy(path, 1, copy_node);
			cpy = ft_lstcpy(((t_path *)path->content)->steps, copy_path);
			ft_printf("else\n");
			((t_path *)cpy2->content)->steps->content = (void *)tunnel;
			((t_path *)cpy2->content)->id = anthill->path_ids++;
			((t_path *)cpy2->content)->finished = 0;
			ft_lstappend(&anthill->paths, cpy2);
		}
		tunnel = tunnel->next;
	}
	return (1);
}

int			find_paths_with_bfs(t_anthill *anthill)
{
	t_list	*path;

	if (anthill->paths_found)
		return (1);
	path = anthill->paths;
	while (path)
	{
		ft_printf("passe ici\n");
		if (((t_path *)path->content)->finished == 0)
			complete_path(anthill, path);
		path = path->next;
		ft_printf("passe ici2\n");
	}
	return (find_paths_with_bfs(anthill));
}
