/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/13 00:26:02 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					end;
	int 				path_id;
	int 				new_path_id;
	bool 				deviation;
	bool				visited;
	t_list			*next;
	t_list			*new_next;
	t_list			*previous;
	t_list				*tunnels;
}						t_room;

typedef struct			s_anthill
{
	int				ant_qty;
	int					room_qty;
	int 			rounds;
	int 			id;
	int 			max_flow;
	t_list				*rooms;
	t_list				*start;
	t_list				*end;
}						t_anthill;

typedef struct			s_tunnel
{
	int			usage;
	t_list			*room;
}				t_tunnel;

typedef struct			s_path
{
	int 							id;
	int 							sent;
	int 							len;
	bool 							used;
	t_list						*room;
}										t_path;

int		create_anthill(t_anthill *anthill);
int		find_paths(t_anthill *anthill);

/*
** ---------------------------- TOOLS ------------------------------------------
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
** ------------------------------ ADD ------------------------------------------
*/
int		add_room(t_anthill *anthill, char *line);
int		add_tunnel(t_anthill *anthill, char *line);
int		add_step(t_list **steps, t_list *room);
int		add_path(t_list **paths);
/*
** ---------------------------- DISPLAY ----------------------------------------
*/
void	print_paths(t_list *paths);
void	print_steps(t_list *steps);
/*
** ----------------------------- INIT ------------------------------------------
*/
int		init_paths(t_list **paths, t_list *start);
/*
** ----------------------------- CLEAN -----------------------------------------
*/
void	clean_paths(t_anthill *anthill);
int		check_dead_end(t_anthill *anthill);
void 	del_steps(void *content, size_t size);


#endif
