/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:46:19 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/21 14:55:55 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>

bool		bfs(t_list *start, t_list *end, t_list **queue)
{
	t_list		*elem;
	t_list		*room;
	bool 			found_augmented_path;

	found_augmented_path = false;
	if (!init_queue(queue, start))
		return (false);
	((t_room *)start->content)->visited = true;
	elem = *queue;
	while (elem)
	{
		room = elem->content;
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

bool		find_paths(t_anthill *anthill, t_list *start
		, t_list *end, t_list **paths)
{
	int			ret;
	t_list	*queue;
	t_list	*previous_paths;

	queue = NULL;
	while (bfs(start, end, &queue))
	{
		previous_paths = *paths;
		*paths = NULL;
		ft_lstdel(&queue, del_steps);
		set_tunnels_usage(end); // set a -1, 0 ou 1 les tunnels->usage de end a start en passant par les previous
		if (!init_paths(paths, start))
			return (false);
		complete_paths(paths);
		ret = test_solution(*paths, anthill->ant_qty); //on teste le nb de lignes
		if (ret > anthill->rounds || ret == 0) // et on compare a la solution precedente
		{
			ft_lstdel(paths, del_steps);
			*paths = previous_paths;
			break ;
		}
		update_data(anthill, ret); // maj des pointeurs next et path_id + valeur anthill->rounds
		ft_lstdel(&previous_paths, del_steps);
	}
	return (anthill->rounds != INT_MAX);
}
