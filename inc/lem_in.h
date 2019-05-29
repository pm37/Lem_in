/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/29 19:13:52 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

typedef struct			s_room
{
	char				*name;
	int					id;
	int					x;
	int					y;
	int					end;
	int					dead_end;
	int					population;
	int					visited_by;
	bool				visited;
	t_list				*tunnels;
}						t_room;

typedef struct			s_anthill
{
	unsigned long long	ant_qty;
	int					room_qty;
	int					paths_found;
	int					path_ids;
	t_list				*start;
	t_list				*end;
	t_list				*rooms;
	t_list				*paths;
}						t_anthill;

typedef struct			s_path
{
	int					len;
	int					finished;
	int					id;
	t_list				*steps;
}						t_path;

int		create_anthill(t_anthill *anthill);
int		add_tunnel(t_anthill *anthill, char *line);
int		add_room(t_anthill *anthill, char *line);
int		find_paths(t_anthill *anthill, t_list *position,
		char *path);
int		init_paths(t_anthill *anthill);
int		find_paths_with_bfs(t_anthill *anthill);

//tools :
int		ret_freetab(int ret, char **tab);
int		ret_freeline(int ret, char **line);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);

#endif
