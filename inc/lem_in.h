/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/10 18:37:41 by pimichau         ###   ########.fr       */
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
	int					population;
	bool				step_to_end;
	bool				visited;
	t_list				*tunnels;
}						t_room;

typedef struct			s_anthill
{
	unsigned long long	ant_qty;
	int					room_qty;
	int					visited;
	t_list				*rooms;
	t_list				*start;
	t_list				*end;
	t_list				*paths;
	t_list				*good_paths;
}						t_anthill;

typedef struct			s_path
{
	int					len;
	bool				stop;
	bool				dead_end;
	t_list				*steps;
}						t_path;

/*
** ------------------------ MAIN FUNCTIONS -------------------------
*/
int		create_anthill(t_anthill *anthill);
int		find_paths(t_anthill *anthill);
int		find_all_paths(t_anthill *anthill);

/*
** ---------------------------- TOOLS ------------------------------
*/
int		ret_freetab(int ret, char **tab);
int		ret_freeline(int ret, char **line);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);
int		copy_path(void *dest, void *src);
int		copy_steps(void *dest, void *src);
t_list	*compare_steps(t_list *l1, t_list *l2);
void	del_path(void *content, size_t size);
/*
** ---------------------------- ADD --------------------------------
*/
int		add_room(t_anthill *anthill, char *line);
int		add_tunnel(t_anthill *anthill, char *line);
int		add_step(t_anthill *anthill, t_list **steps, t_list *room);
int		add_path(t_anthill *anthill, t_list *path, t_list *room);
/*
** ------------------------- DISPLAY ------------------------------- 
*/
void	print_paths(t_list *paths);
void	print_steps(t_list *steps);
/*
** -------------------------- INIT --------------------------------- 
*/
int		init_paths(t_anthill *anthill);
/*
** -------------------------- CLEAN ----------------------------------- 
*/
void	clean_paths(t_anthill *anthill);
int		check_dead_end(t_anthill *anthill);


#endif
