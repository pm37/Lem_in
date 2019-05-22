/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:25:24 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/22 20:42:44 by pimichau         ###   ########.fr       */
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

int			find_paths(t_anthill *anthill, t_list *position, t_list *end, char *path)
{
	t_list	*tunnel;
	t_list	*room;
	char	*tmp;

	if (start == end)
		return (add_path(anthill, path));
	tunnel = position->content->tunnels;
	while (tunnel)
	{
		room = (t_list *)tunnel->content;
		if (!ft_strstr_delim(path, room->content->name, '-'))
		{
			if (!(tmp = ft_strdup(path)))
				return (0);
			variadic_strjoin(&tmp, "-%s", room->content->name);
			find_paths(room, end, tmp);
		}
		tunnel = tunnel->next;
	}
	ft_strdel(&path);
	return (1);
}
