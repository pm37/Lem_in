/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:25:24 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/23 18:58:37 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	add_path(t_anthill *anthill, char *found_path)
{
	t_path	new_path;
	t_list	*new;


	new_path.path = found_path;
	new_path.len = count_occurence(found_path, '-');
	if (!(new = ft_lstnew(&new_path, sizeof(t_path))))
		return (0);
	ft_lstappend(&anthill->paths, new);
	return (1);
}

static int	join_paths(t_anthill *anthill, char *found_path, char *name)
{
	t_list	*paths;
	char	*ret;
	char	*tmp;

	paths = anthill->paths;
	while (paths)
	{
		if ((ret = ft_strstr(((t_path *)paths->content)->path, name)))
		{
			tmp = ft_strdup(found_path);
			variadic_strjoin(&tmp, "-%s", ret);
			add_path(anthill, tmp);
			ft_strdel(&tmp);
		}
		paths = paths->next;
	}
	return (1);
}

static int	check_dead_end(t_list *paths, char *name)
{
	t_list	*elem;

	elem = paths;
	while (elem)
	{
		if (ft_strstr_delim(((t_path *)(elem->content))->path, name, '-'))
			return (0);
		elem = elem->next;
	}
	return (1);
}

int			find_paths(t_anthill *anthill, t_list *position, char *path)
{
	t_list	*tunnel;
	t_list	*room;
	char	*tmp;

	if (position == anthill->start)
		return (add_path(anthill, path));
	if (((t_room *)(position->content))->paths_discovered == 1)
		return (join_paths(anthill, path,
		((t_room *)(position->content))->name));
	tunnel = ((t_room *)(position->content))->tunnels;
	while (tunnel)
	{
		room = (t_list *)tunnel->content;
		if (!ft_strstr_delim(path, ((t_room *)(room->content))->name, '-')
		&& ((t_room *)(position->content))->dead_end == 0)
		{
			if (!(tmp = ft_strdup(path)))
				return (0);
			variadic_strjoin(&tmp, "-%s", ((t_room *)(room->content))->name);
			find_paths(anthill, room, tmp);
		}
		tunnel = tunnel->next;
	}
	if (check_dead_end(anthill->paths, ((t_room *)(room->content))->name))
		((t_room *)(position->content))->dead_end = 1;
	else
		((t_room *)(position->content))->paths_discovered = 1;
	ft_strdel(&path);
	return (1);
}
