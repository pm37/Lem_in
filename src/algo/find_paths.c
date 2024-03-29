/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/02 11:58:08 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

bool			bfs(t_list *start, t_list *end, t_list **queue)
{
	t_list	*elem;
	t_list	*room;
	bool	found_augmented_path;

	found_augmented_path = false;
	if (!init_queue(queue, start))
		return (false);
	((t_room *)start->content)->visited = true;
	elem = *queue;
	while (elem)
	{
		room = ((t_queue *)elem->content)->room;
		if (!complete_queue(elem, end))
			return (false);
		if (((t_room *)end->content)->visited)
		{
			found_augmented_path = true;
			break ;
		}
		elem = elem->next;
	}
	return (found_augmented_path);
}

static bool		find_paths(t_anthill *anthill, t_list **paths)
{
	unsigned long	ret;
	t_list			*queue;
	t_list			*previous_paths;

	queue = NULL;
	while (bfs(anthill->start, anthill->end, &queue))
	{
		previous_paths = *paths;
		*paths = NULL;
		set_tunnels_usage(anthill->end, &queue);
		if (!init_paths(paths, anthill->start, anthill->option))
			return (false);
		complete_paths(paths);
		ret = test_solution(anthill, *paths, anthill->ant_qty);
		if (ret >= anthill->rounds || ret == 0)
		{
			ft_lstdel(paths, del_steps);
			*paths = previous_paths;
			break ;
		}
		update_data(anthill, ret, paths);
		ft_lstdel(&previous_paths, del_steps);
	}
	ft_lstdel(&queue, del_steps);
	return (anthill->rounds != LONG_MAX && ret != 0);
}

bool			get_paths(t_anthill *anthill, t_list *start, t_list *end
			, t_list **paths)
{
	if (start_linked_to_end(start, end))
		return (init_the_only_path(paths, anthill));
	return (find_paths(anthill, paths));
}
