/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:25:24 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/29 13:37:00 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
static int	add_path(t_anthill *anthill, char *found_path)
{
	t_path	new_path;
	t_list	*new;

	//debug
	//ft_printf("add path\n");
	new_path.path = found_path;
	new_path.len = count_occurence(found_path, '-');
	if (!(new = ft_lstnew(&new_path, sizeof(t_path))))
		return (0);
	ft_lstappend(&anthill->paths, new);
	//debug
	//ft_printf("added path\n");
	return (1);
}

static int	join_paths(t_anthill *anthill, char *found_path, char *name)
{
	t_list	*paths;
	char	*ret;
	char	*tmp;

	//debug
	ft_printf("join path : name = %s, start = %s, end = %s\n", name, 
	((t_room *)anthill->start->content)->name, 
	((t_room *)anthill->end->content)->name);
	paths = anthill->paths;
	while (paths)
	{
		if ((ret = ft_strstr_delim(((t_path *)paths->content)->path, name, '-'))
			&& *ret)
		{
			ft_printf("ret : %s\n", ret); 
			tmp = ft_strdup(found_path);
			variadic_strjoin(&tmp, "-%s", ret);
			add_path(anthill, tmp);
			ft_strdel(&tmp);
		}
		paths = paths->next;
	}
	//debug
	ft_printf("joined path\n");
	return (1);
}

static int	check_dead_end(t_list *paths, char *name)
{
	t_list	*elem;

	elem = paths;
	//debug
	ft_printf("check dead-end\n");
	while (elem)
	{
		if (ft_strstr_delim(((t_path *)(elem->content))->path, name, '-'))
			return (0);
		elem = elem->next;
	}
	//debug
	ft_printf("checked dead-end\n");
	return (1);
}

int			find_paths(t_anthill *anthill, t_list *position, char *path)
{
	t_list	*tunnel;
	t_list	*room;
	char	*tmp;

	//debug
	ft_printf("find path\n");
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
	//debug
	ft_printf("found path\n");
	return (1);
}*/
