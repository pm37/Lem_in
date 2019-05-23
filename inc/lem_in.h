/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/23 18:58:03 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct			s_room
{
	char				*name;
	int					id;
	int					x;
	int					y;
	int					end;
	int					dead_end;
	int					paths_discovered;
	int					population;
	t_list				*tunnels;
}						t_room;

typedef struct			s_anthill
{
	unsigned long long	ant_qty;
	int					room_qty;
	t_list				*start;
	t_list				*end;
	t_list				*rooms;
	t_list				*paths;
}						t_anthill;

typedef struct			s_path
{
	int					len;
	char				*path;
}						t_path;

int		create_anthill(t_anthill *anthill);
int		add_tunnel(t_anthill *anthill, char *line);
int		add_room(t_anthill *anthill, char *line);
int		find_paths(t_anthill *anthill, t_list *position,
		char *path);

//tools :
int		ret_freetab(int ret, char **tab);
int		ret_freeline(int ret, char **line);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);

#endif
