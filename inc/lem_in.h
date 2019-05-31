/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/31 18:32:41 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

typedef struct			s_room
{
	char				*name;
	int					id;
	int					x;
	int					y;
	int					end;
	int					dead_end;
	int					population;
	bool				visited;
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
	t_list				*steps;
}						t_path;

int		create_anthill(t_anthill *anthill);
int		find_paths(t_anthill *anthill);

/*
** ---------------------------- TOOLS ------------------------------
*/
int		ret_freetab(int ret, char **tab);
int		ret_freeline(int ret, char **line);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);
int		copy_path(void *dest, void *src);
int		copy_steps(void *dest, void *src);
/*
** ---------------------------- ADD --------------------------------
*/
int		add_room(t_anthill *anthill, char *line);
int		add_tunnel(t_anthill *anthill, char *line);
int		add_step(t_list **steps, t_list *room);
int		add_path(t_anthill *anthill, t_list *path, t_list *room);
/*
** ------------------------- DISPLAY ------------------------------- 
*/
void	print_paths(t_list *paths);
/*
** -------------------------- INIT --------------------------------- 
*/
int		init_paths(t_anthill *anthill);


#endif
